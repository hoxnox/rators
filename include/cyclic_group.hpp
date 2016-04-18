/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160418 15:39:24 */

#pragma once
#include <rators_config.h>
#include <math.hpp>

namespace rators {

template<std::size_t N>
class cyclic_group
{
public:

	cyclic_group(std::array<bigint_t, N> sizes, bigint_t seed = 0x12345)
		: sizes_(sizes)
		, approx_sizes_(find_gt_coprime(sizes))
	{
		std::srand((int)seed);
		for (size_t i = 0; i < N; ++i)
			seed_[i] = ((bigint_t)std::rand())%sizes_[i];
		// TODO: zero
		approx_size_ = 1;
		for (auto i : approx_sizes_)
			approx_size_ *= (i == 0 ? 1 : i);
	}

	class const_iterator;
	const_iterator begin() const;
	const_iterator end() const;

	/**@brief total elements in the group*/
	bigint_t size() const;
	bool     contains(const std::array<bigint_t, N>& elem) const;

private:
	std::array<bigint_t, N> sizes_;
	std::array<bigint_t, N> approx_sizes_;
	bigint_t                approx_size_;
	std::array<bigint_t, N> seed_;

friend class cyclic_group<N>::const_iterator;
};

template<std::size_t N>
class cyclic_group<N>::const_iterator
	: public std::iterator<std::input_iterator_tag, std::array<bigint_t, N>, bigint_t>
{
public:
	const_iterator(const const_iterator& copy) = default;
	const_iterator&         operator=(const const_iterator& copy) = default;
	bool                    operator==(const const_iterator& rhv) const;
	bool                    operator!=(const const_iterator& rhv) const;
	const_iterator          operator++(int);
	const_iterator          operator++();
	const_iterator          operator+=(int n);
	const_iterator          operator+(int n);
	std::array<bigint_t, N> operator*() const { return curr_; }

private:
	const_iterator() = default;
	std::array<bigint_t, N> curr_;
	bigint_t                curr_pos_;
	const cyclic_group* owner_{nullptr};

friend class cyclic_group<N>;
};

////////////////////////////////////////////////////////////////////////

template<std::size_t N> inline typename cyclic_group<N>::const_iterator
cyclic_group<N>::begin() const
{
	const_iterator rs;
	rs.curr_pos_ = 0;
	rs.curr_ = seed_;
	rs.owner_ = this;
	return rs;
}

template<std::size_t N> inline typename cyclic_group<N>::const_iterator
cyclic_group<N>::end() const
{
	const_iterator rs;
	rs.curr_pos_ = approx_size_;
	rs.curr_ = seed_;
	rs.owner_ = this;
	return rs;
}

template<std::size_t N> inline bool
cyclic_group<N>::contains(const std::array<bigint_t, N>& el) const
{
	for (auto i = 0; i < N; ++i)
		if (el[i] >= sizes_[i])
			return false;
	return true;
}

template<std::size_t N> bigint_t
cyclic_group<N>::size() const
{
	bigint_t sz = 1;
	std::for_each(sizes_.begin(), sizes_.end(),
			[&sz](const bigint_t& n){ sz *= n; });
	return sz;
}

template<size_t N> inline typename cyclic_group<N>::const_iterator
cyclic_group<N>::const_iterator::operator++()
{
	if (!owner_)
		return *this;
	if (curr_pos_ >= owner_->approx_size_)
		return *this;
	while (curr_pos_ < owner_->approx_size_)
	{
		for (ssize_t i = owner_->approx_sizes_.size() - 1; i >= 0; --i)
		{
			if (curr_[i] < owner_->approx_sizes_[i] - 1)
				++curr_[i];
			else
				curr_[i] = 0;
		}
		++curr_pos_;
		if (owner_->contains(curr_))
			break;
	}
	return *this;
}

template<std::size_t N> inline typename cyclic_group<N>::const_iterator
cyclic_group<N>::const_iterator::operator++(int)
{
	const_iterator prev = *this;
	operator++();
	return prev;
}

template<std::size_t N> inline typename cyclic_group<N>::const_iterator
cyclic_group<N>::const_iterator::operator+=(int n)
{
	return *this = *this + n;
}

template<std::size_t N> inline typename cyclic_group<N>::const_iterator
cyclic_group<N>::const_iterator::operator+(int n)
{
	const_iterator rs(*this);
	for (int i = 0; i < n; ++i)
	{
		if (rs == owner_->end())
			return rs;
		++rs;
	}
	return rs;
}

template<std::size_t N> inline bool
cyclic_group<N>::const_iterator::operator==(const const_iterator& rhv) const
{
	if (owner_ != rhv.owner_ || curr_.size() != rhv.curr_.size())
		return false;
	if (curr_pos_ >= owner_->approx_size_ && rhv.curr_pos_ >= rhv.owner_->approx_size_)
		return true;
	if (curr_pos_ != rhv.curr_pos_)
		return false;
	for (bigint_t i = 0; i < curr_.size(); ++i)
		if (curr_[i] != rhv.curr_[i])
			return false;
	return true;
}

template<std::size_t N> inline bool
cyclic_group<N>::const_iterator::operator!=(const const_iterator& rhv) const
{
	return !operator==(rhv);
}

} // namespace

