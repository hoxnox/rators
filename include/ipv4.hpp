/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160411 11:31:17 */

#pragma once
#include <memory>
#include <algorithm>
#include <iterator>
#include <rators_config.h>
#include "cidr.hpp"
#include "lpfst.hpp"

namespace rators {

class ipv4
{
public:
	class const_iterator;
	ipv4(cidr_v4 addr);
	ipv4(cidr_v4 begin, cidr_v4 end);
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator get(cidr_v4 addr) const;
	size_t size() const { return space_.size(); }

private:
	integers<uint32_t> space_;

friend class ipv4::const_iterator;
};

class ipv4::const_iterator
	: public std::iterator<std::input_iterator_tag, std::string, uint32_t>
{
public:
	const_iterator() {}
	const_iterator(const const_iterator& copy) = default;
	const_iterator& operator=(const const_iterator& copy) = default;
	bool            operator==(const const_iterator& rhv) const;
	bool            operator!=(const const_iterator& rhv) const;
	const_iterator  operator++(int);
	const_iterator  operator++();
	const_iterator  operator+=(int n);
	const_iterator  operator+(uint32_t n);
	std::string     operator*() const;
	uint32_t        distance(const const_iterator& rhv) const
	{
		if (parent_ && parent_ == rhv.parent_)
			return pos_.distance(rhv.pos_);
		std::cout << "Nooooo" << std::endl;
		return 0;
	}

private:
	const_iterator(const integers<uint32_t>::const_iterator& pos) : pos_(pos) {}
	integers<uint32_t>::const_iterator pos_;
	const ipv4*                        parent_{nullptr};

friend class ipv4;
};

////////////////////////////////////////////////////////////////////////

/**@note address of the network excluded*/
ipv4::ipv4(cidr_v4 addr)
	: space_(addr.is_net() ?
		integers<uint32_t>{
			(((uint32_t)addr>>(32-addr.mask()))<<(32-addr.mask())) + 1,
			(((uint32_t)addr>>(32-addr.mask()))<<(32-addr.mask()))|(0xffffffff>>addr.mask())
		}
		: integers<uint32_t>{(uint32_t)addr, (uint32_t)addr}
	)
{
}

/**@note begin is included*/
ipv4::ipv4(cidr_v4 begin, cidr_v4 end)
	: space_((uint32_t)begin, (uint32_t)end)
{
}

inline ipv4::const_iterator
ipv4::begin() const
{
	const_iterator begin(space_.begin());
	begin.parent_ = this;
	return begin;
}

inline ipv4::const_iterator
ipv4::end() const
{
	const_iterator end(space_.end());
	end.parent_ = this;
	return end;
}

inline ipv4::const_iterator
ipv4::get(cidr_v4 addr) const
{
	const_iterator rs(space_.get((uint32_t)addr));
	rs.parent_ = this;
	return rs;
}

inline ipv4::const_iterator
ipv4::const_iterator::operator++()
{
	++pos_;
	if (pos_ == parent_->space_.end())
		return pos_;
	return *this;
}

inline ipv4::const_iterator
ipv4::const_iterator::operator++(int)
{
	const_iterator prev = *this;
	operator++();
	return prev;
}

inline ipv4::const_iterator
ipv4::const_iterator::operator+=(int n)
{
	return *this = *this + n;
}

inline ipv4::const_iterator
ipv4::const_iterator::operator+(uint32_t n)
{
	const_iterator rs(*this);
	if (rs.pos_ == parent_->space_.end())
		return rs.pos_;
	rs.pos_ += n - 1;
	rs.operator++();
	return rs;
}

inline bool
ipv4::const_iterator::operator==(const ipv4::const_iterator& rhv) const
{
	return  pos_ == rhv.pos_ && parent_ == rhv.parent_;
}

inline bool
ipv4::const_iterator::operator!=(const ipv4::const_iterator& rhv) const
{
	return !operator==(rhv);
}

inline std::string
ipv4::const_iterator::operator*() const
{
	if (pos_ == parent_->space_.end())
		return std::string();
	cidr_v4 addr(*pos_, 32);
	if (pos_ == parent_->space_.end())
		return std::string();
	return addr.str(true);
}

} // namespace

namespace std {

typename iterator_traits<rators::ipv4::const_iterator>::difference_type
distance (const rators::ipv4::const_iterator& first, const rators::ipv4::const_iterator& last)
{
	return first.distance(last);
}

} // namespace

