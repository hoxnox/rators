/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160407 11:27:23 */

#pragma once
#include <memory>
#include <algorithm>
#include <iterator>
#include <rators_config.h>

namespace rators {

template<class IntT>
class integers
{
public:
	class const_iterator;
	integers(IntT begin, IntT end) : first_(begin), last_(end) {}
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator get(IntT value) const;
	size_t size() const { return last_ < first_ ? 0 : last_ - first_ + 1; }

private:
	IntT first_;
	IntT last_;

friend class integers::const_iterator;
};

template<class IntT>
class integers<IntT>::const_iterator 
	: public std::iterator<std::input_iterator_tag, IntT, IntT>
{
public:
	const_iterator() {}
	const_iterator(const const_iterator& copy) = default;
	const_iterator& operator=(const const_iterator& copy) = default;
	bool            operator==(const const_iterator& rhv) const;
	bool            operator!=(const const_iterator& rhv) const { return !operator==(rhv); }
	const_iterator  operator++();
	const_iterator  operator++(int);
	const_iterator  operator+=(int n);
	const_iterator  operator+(IntT n);
	IntT            operator*() const { return curr_; }
	IntT            distance(const const_iterator& rhv) const
	{
		if (is_end)
			return 0;
		if (curr_ <= rhv.curr_ && rhv.is_end)
			return rhv.curr_ - curr_ + 1;
		if (curr_ < rhv.curr_)
			return rhv.curr_ - curr_;
		std::cout << "Fuuuuu" << std::endl;
		return 0;
	}

private:
	bool is_end{false};
	IntT curr_{0};
	IntT last_{0};

friend class integers;
};

////////////////////////////////////////////////////////////////////////

template<class IntT> inline typename integers<IntT>::const_iterator
integers<IntT>::begin() const
{
	const_iterator begin;
	begin.curr_ = first_;
	begin.last_ = last_;
	return begin;
}

template<class IntT> inline typename integers<IntT>::const_iterator
integers<IntT>::end() const
{
	const_iterator end;
	end.curr_ = last_;
	end.last_ = last_;
	end.is_end = true;
	return end;
}

template<class IntT> inline typename integers<IntT>::const_iterator
integers<IntT>::get(IntT val) const
{
	if (val < first_ || val > last_)
		return end();
	const_iterator rs;
	rs.curr_ = val;
	rs.last_ = last_;
	return rs;
}

template<class IntT> inline typename integers<IntT>::const_iterator
integers<IntT>::const_iterator::operator++()
{
	if (last_ == 0)
	{
		curr_ = 0;
		last_ = 0;
		return *this;
	}
	if (curr_ >= last_)
	{
		curr_ = last_;
		is_end = true;
		return *this;
	}
	++curr_;
	return *this;
}

template<class IntT> inline typename integers<IntT>::const_iterator
integers<IntT>::const_iterator::operator++(int)
{
	const_iterator prev = *this;
	operator++();
	return prev;
}

template<class IntT> inline typename integers<IntT>::const_iterator
integers<IntT>::const_iterator::operator+=(int n)
{
	return *this = *this + n;
}

template<class IntT> inline typename integers<IntT>::const_iterator
integers<IntT>::const_iterator::operator+(IntT n)
{
	const_iterator rs(*this);
	if (rs.last_ == 0)
	{
		rs.curr_ = 0;
		rs.last_ = 0;
		return *this;
	}
	if (rs.curr_ + n >= rs.last_)
	{
		rs.curr_ = last_;
		rs.last_ = last_;
		rs.is_end = true;
		return *this;
	}
	rs.curr_ += n;
	return rs;
}

template<class IntT> inline bool
integers<IntT>::const_iterator::operator==(const const_iterator& rhv) const
{
	return  curr_ == rhv.curr_ && last_ == rhv.last_ && is_end == rhv.is_end;
}

} // namespace

