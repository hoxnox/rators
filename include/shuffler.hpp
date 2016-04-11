/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160407 11:27:23 */

#pragma once
#include <memory>
#include <algorithm>
#include <iterator>
#include <rators_config.h>

namespace rators {

template<class FwdIterator>
class shuffler
{
public:
	class const_iterator;
	shuffler(FwdIterator begin, FwdIterator end,
	         bigint_t cycles_cnt = 1, bigint_t seed = 1);
	const_iterator begin() const;
	const_iterator end() const;
	//const_itarator get(bigint_t position, bigint_t cycle_no) const;
	const_iterator get_by_state(bigint_t state, bigint_t cycle_no) const;

private:
	bigint_t    seed_{0};
	bigint_t    size_{0};
	bigint_t    pow2_approx_{0};
	bigint_t    cycles_cnt_{1};
	FwdIterator it_begin_;

friend class shuffler::const_iterator;
};

template<class FwdIterator>
class shuffler<FwdIterator>::const_iterator
{
public:
	using value_type =typename std::iterator_traits<FwdIterator>::value_type;
	const_iterator(const const_iterator& copy) = default;
	const_iterator& operator=(const const_iterator& copy) = default;
	bool            operator==(const const_iterator& rhv) const;
	bool            operator!=(const const_iterator& rhv) const { return !operator==(rhv); }
	const_iterator  operator++();
	value_type operator*() const { return *(parent_->it_begin_ + (state_ - 1)); }

private:
	const_iterator() = default;
	const shuffler* parent_{nullptr};
	bigint_t        state_{1};
	bigint_t        cycle_no_{0};

friend class shuffler;
};

////////////////////////////////////////////////////////////////////////

const uint16_t PRIME_POLY[64] = {
	   1, 3, 3, 3, 5, 3, 3, 29, 17, 9, 5, 83, 27, 43, 3, 45, 9, 129, 39,
	   9, 5, 3, 33, 27, 9, 71, 39, 9, 5, 83, 9, 197, 8193, 231, 5, 119,
	   83, 99, 17, 57, 9, 153, 89, 101, 27, 449, 33, 183, 113, 29, 75,
	   9, 71, 125, 71, 149, 129, 99, 123, 3, 39, 105, 3, 27
};

inline bigint_t
register_shift(bigint_t reg, uint8_t reg_size)
{
	if (reg & 1)
		reg = ((reg ^ PRIME_POLY[reg_size]) >> 1) | (1 << reg_size);
	else
		reg >>= 1;
	return reg;
}

inline uint16_t
get_pow2_approx(bigint_t val)
{
	uint16_t pow2_approx = 0;
	if(val > 9223372036854775808UL)
	{
		pow2_approx = 63;
	}
	else
	{
		while(pow2_approx < 64)
		{
			if(val >= (1 << (pow2_approx + 1)))
				++pow2_approx;
			else
				break;
		}
	}
	return pow2_approx + 1;
}

template<class FwdIterator>
shuffler<FwdIterator>::shuffler(FwdIterator begin, FwdIterator end,
                                bigint_t cycles_cnt, bigint_t seed)
	: seed_(seed == 0 ? 1 : seed)
	, size_(static_cast<bigint_t>(end - begin))
	, pow2_approx_(get_pow2_approx(size_))
	, cycles_cnt_(cycles_cnt)
	, it_begin_(begin)
{
	if (pow2_approx_ >= sizeof(bigint_t)*8 || cycles_cnt_ == 0)
	{
		size_ = 0;
		pow2_approx_ = 0;
		cycles_cnt_ = 0;
		seed_ = 0;
	}
	bigint_t mask;
	std::uninitialized_fill((char*)&mask, (char*)&mask + pow2_approx_, 0xFF);
	seed_ &= mask;
	seed_ = register_shift(seed_, pow2_approx_);
	while(seed_ >= size_)
		seed_ = register_shift(seed_, pow2_approx_);
}

template<class FwdIterator> inline typename shuffler<FwdIterator>::const_iterator
shuffler<FwdIterator>::begin() const
{
	const_iterator begin;
	begin.parent_ = this;
	begin.state_ = seed_;
	begin.cycle_no_ = 0;
	return begin;
}

template<class FwdIterator> inline typename shuffler<FwdIterator>::const_iterator
shuffler<FwdIterator>::end() const
{
	const_iterator end;
	end.parent_ = this;
	end.state_ = 0;
	end.cycle_no_ = cycles_cnt_;
	return end;
}

template<class FwdIterator> inline typename shuffler<FwdIterator>::const_iterator
shuffler<FwdIterator>::get_by_state(bigint_t state, bigint_t cycle_no) const
{
	const_iterator rs;
	rs.parent_ = this;
	rs.state_ = state;
	rs.cycle_no_ = cycle_no;
	return rs;
}

template<class FwdIterator> inline typename shuffler<FwdIterator>::const_iterator
shuffler<FwdIterator>::const_iterator::operator++()
{
	if (operator==(parent_->end()))
		return *this;
	state_ = register_shift(state_, parent_->pow2_approx_);
	while(state_ > parent_->size_)
		state_ = register_shift(state_, parent_->pow2_approx_);
	if (state_ == parent_->seed_)
		++cycle_no_;
	if (cycle_no_ >= parent_->cycles_cnt_)
		operator=(parent_->end());
	return *this;
}

template<class FwdIterator> inline bool
shuffler<FwdIterator>::const_iterator::operator==(const const_iterator& rhv) const
{
	return  parent_ == rhv.parent_
	     && state_ == rhv.state_
	     && cycle_no_ == rhv.cycle_no_;
}

} // namespace

