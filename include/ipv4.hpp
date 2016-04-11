/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160411 11:31:17 */

#pragma once
#include <memory>
#include <algorithm>
#include <iterator>
#include <rators_config.h>
#include "cidr.h"

namespace rators {

class ipv4
{
public:
	static ipv4 inet();
	ipv4(std::string addr = "0.0.0.0/0");
	ipv4(cidr_v4 begin, cidr_v4 end);

	void append_to_blacklist(const cidr_v4& addr)
		{ blacklist_.emp }

	class const_iterator
	{
	public:
		const_iterator(const const_iterator& copy) = default;
		const_iterator& operator=(const const_iterator& copy) = default;
		bool            operator==(const const_iterator& rhv) const;
		bool            operator!=(const const_iterator& rhv) const;
		const_iterator  operator++();
		IntT operator*() const { return curr_; }

	private:
		const_iterator() = default;
		IntT curr_;
		IntT last_;

	friend class integers;
	};

	const_iterator begin() const;
	const_iterator end() const;

private:
	cidr_v4             fisrt_;
	cidr_v4             last_;
	bool                skip_private_{true};
	std::unordered_set<cidr_t> blacklist_;

friend class integers::const_iterator;
};

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
	end.curr_ = 0;
	end.last_ = 0;
	return end;
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
		curr_ = 0;
		last_ = 0;
		return *this;
	}
	++curr_;
	return *this;
}

template<class IntT> inline bool
integers<IntT>::const_iterator::operator==(const const_iterator& rhv) const
{
	return  curr_ == rhv.curr_ && last_ == rhv.last_;
}

template<class IntT> inline bool
integers<IntT>::const_iterator::operator!=(const const_iterator& rhv) const
{
	return !operator==(rhv);
}

} // namespace

