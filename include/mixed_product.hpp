/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160420 09:11:52 */

#pragma once
#include <rators_config.h>
#include <array>

namespace rators {

template<class Iter, std::size_t N>
class mixed_product
{
public:
	using ObjT=typename std::iterator_traits<Iter>::value_type;
	struct range_t
	{
		range_t(Iter begin, Iter end) : begin(begin), end(end) {}
		Iter begin;
		Iter end;
	};
	mixed_product(const std::array<range_t, N>&& inputs,
	              bigint_t mix_seed = 0x98765);
	class const_iterator;
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator get_by_state(std::array<bigint_t, N> state) const;

	/**@brief total elements in the CP*/
	//bigint_t size() const { return cnt_total_; }

private:
	mode_t mode_;
	std::array<range_t, N>      iterators_;
	std::array<bigint_t, N>     sizes_{};
	std::unique_ptr<cyclic_group<N> > selector_{nullptr};
friend class mixed_product<Iter, N>::const_iterator;
};

template<class Iter, std::size_t N>
class mixed_product<Iter, N>::const_iterator
	: public std::iterator<std::input_iterator_tag, std::array<mixed_product::ObjT, N>, bigint_t>
{
public:
	const_iterator(const const_iterator& copy) = default;
	const_iterator&     operator=(const const_iterator& copy) = default;
	bool                operator==(const const_iterator& rhv) const;
	bool                operator!=(const const_iterator& rhv) const {return !operator==(rhv);}
	const_iterator      operator++(int);
	const_iterator      operator++();
	std::array<ObjT, N> operator*();
private:
	bigint_t distance(Iter a, Iter b) { return static_cast<bigint_t>(std::distance(a, b)); }
	const_iterator(const mixed_product<Iter, N>& owner);
	const mixed_product<Iter, N>*            owner_;
	typename cyclic_group<N>::const_iterator curr_pos_;
	std::array<Iter, N>                      curr_pos_iters_;
friend class mixed_product<Iter, N>;
};

////////////////////////////////////////////////////////////////////////

template<class Iter, std::size_t N>
mixed_product<Iter, N>::mixed_product(const std::array<range_t, N>&& inputs,
                                      bigint_t mix_seed)
	: iterators_(inputs)
{
	for (size_t i = 0; i < N; ++i)
	{
		sizes_[i] = distance(inputs[i].begin, inputs[i].end);
	}
	selector_.reset(new cyclic_group<N>(sizes_, mix_seed));
}

template<class Iter, std::size_t N>
mixed_product<Iter, N>::const_iterator::const_iterator(const mixed_product<Iter, N>& owner)
	: owner_(&owner)
	, curr_pos_(owner_->selector_->begin())
{
	std::array<bigint_t, N> start_pos = *(owner_->selector_->begin());
	for (size_t i = 0; i < N; ++i)
	{
		curr_pos_iters_[i] = owner_->iterators_[i].begin;
		curr_pos_iters_[i] += (int)start_pos[i];
	}
}

template<class Iter, std::size_t N> typename mixed_product<Iter, N>::const_iterator
mixed_product<Iter, N>::begin() const
{
	const_iterator rs(*this);
	return rs;
}

template<class Iter, std::size_t N> typename mixed_product<Iter, N>::const_iterator
mixed_product<Iter, N>::end() const
{
	const_iterator rs(*this);
	rs.curr_pos_ = selector_->end();
	return rs;
}

template<class Iter, std::size_t N> typename mixed_product<Iter, N>::const_iterator
mixed_product<Iter, N>::get_by_state(std::array<bigint_t, N> state) const
{
	const_iterator rs(*this);
	rs.curr_pos_ = selector_->get_by_state(state);
	std::array<bigint_t, N> pos = *rs.curr_pos_;
	for (size_t i = 0; i < N; ++i)
		rs.curr_pos_iters_[i] = iterators_[i].begin + pos[i];
	return rs;
}

template<class Iter, std::size_t N> typename mixed_product<Iter, N>::const_iterator
mixed_product<Iter, N>::const_iterator::operator++(int)
{
	const_iterator prev = *this;
	operator++();
	return prev;
}

template<class Iter, std::size_t N> typename mixed_product<Iter, N>::const_iterator
mixed_product<Iter, N>::const_iterator::operator++()
{
	auto prev_pos = *curr_pos_;
	++curr_pos_;
	for (size_t i = 0; i < N; ++i)
	{
		if ((*curr_pos_)[i] == 0)
		{
			curr_pos_iters_[i] = owner_->iterators_[i].begin;
		}
		else if ((*curr_pos_)[i] > prev_pos[i])
		{
			curr_pos_iters_[i] += (*curr_pos_)[i] - prev_pos[i];
		}
		else
		{
			curr_pos_iters_[i] = owner_->iterators_[i].begin;
			curr_pos_iters_[i] += (*curr_pos_)[i];
		}
	}
	return *this;
}

template<class Iter, std::size_t N> bool
mixed_product<Iter, N>::const_iterator::operator==(const const_iterator& rhv) const
{
	if (owner_ != rhv.owner_)
		return false;
	return curr_pos_ == rhv.curr_pos_;
}

template<class Iter, std::size_t N> typename std::array<typename mixed_product<Iter, N>::ObjT, N>
mixed_product<Iter, N>::const_iterator::operator*()
{
	std::array<bigint_t, N> pos = *curr_pos_;
	std::array<typename mixed_product<Iter, N>::ObjT, N> rs;
	for (size_t i = 0; i < N; ++i)
		rs[i] = *(curr_pos_iters_[i]);
	return rs;
}

} // namespace

