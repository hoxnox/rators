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
	static ipv4 internet();
	ipv4(cidr_v4 addr);
	ipv4(cidr_v4 begin, cidr_v4 end);
	void append_to_blacklist(const cidr_v4& addr) { blacklist_.insert(addr); }
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator get(cidr_v4 addr) const;
	size_t size() const { return space_.size(); }

private:
	integers<uint32_t> space_;
	lpfst   blacklist_;

friend class ipv4::const_iterator;
};

class ipv4::const_iterator
{
public:
	const_iterator(const const_iterator& copy) = default;
	const_iterator& operator=(const const_iterator& copy) = default;
	bool            operator==(const const_iterator& rhv) const;
	bool            operator!=(const const_iterator& rhv) const;
	const_iterator  operator++(int);
	const_iterator  operator++();
	const_iterator operator+=(int n);
	cidr_v4         operator*();

private:
	const_iterator(const integers<uint32_t>::const_iterator& pos) : pos_(pos) {}
	integers<uint32_t>::const_iterator pos_;
	const ipv4*                        parent_;

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

ipv4 ipv4::internet()
{
	ipv4 result({"1.0.0.1"}, {"223.255.255.255"});
	// RFC-1122: This host on this network
	result.append_to_blacklist({"0.0.0.0/8"});
	// RFC-6598: Shared address space
	result.append_to_blacklist({"100.64.0.0/10"});
	// RFC-3927: Link local
	result.append_to_blacklist({"169.254.0.0/16"});
	// RFC-1918: Private use
	result.append_to_blacklist({"10.0.0.0/8"});
	// RFC-1918: Private use
	result.append_to_blacklist({"172.16.0.0/12"});
	// RFC-6890: IETF Protocol Assignments
	result.append_to_blacklist({"192.0.0.0/24"});
	// RFC-5737: Documentation (TEST-NET-1)
	result.append_to_blacklist({"192.0.2.0/24"});
	// RFC-3068: 6to4 Relay Anycast
	result.append_to_blacklist({"192.88.99.0/24"});
	// RFC-1918: Private-Use
	result.append_to_blacklist({"192.168.0.0/16"});
	// RFC-2544: Benchmarking
	result.append_to_blacklist({"192.18.0.0/15"});
	// RFC-5737: Documentation (TEST-NET-2)
	result.append_to_blacklist({"198.51.100.0/24"});
	// RFC-5737: Documentation (TEST-NET-3)
	result.append_to_blacklist({"203.0.113.0/24"});
	// RFC-1112: Reserved
	result.append_to_blacklist({"240.0.0.0/4"});
	// RFC-0919: Limited Broadcast
	result.append_to_blacklist({"255.255.255.255/32"});
	return result;
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
	if (parent_->blacklist_.check({*pos_, 32}))
		operator++();
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
	if (pos_ == parent_->space_.end())
		return pos_;
	pos_ += n - 1;
	operator++();
	return *this;
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

inline cidr_v4
ipv4::const_iterator::operator*()
{
	if (pos_ == parent_->space_.end())
		return cidr_v4("0.0.0.0/0");
	cidr_v4 addr(*pos_, 32);
	if (parent_->blacklist_.check(addr))
	{
		operator++();
		addr = cidr_v4(*pos_, 32);
	}
	if (pos_ == parent_->space_.end())
		return cidr_v4("0.0.0.0/0");
	return addr;
}

} // namespace

