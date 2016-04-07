/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160405 11:39:23 */

#pragma once
#include <string>
#include "rators_config.h"
#include "cidr.hpp"

namespace rators {

class ipv4_rator
{
public:
	ipv4_rator(std::string cidr = "0.0.0.0/0",
	           SizeT mix = 0,
	           SizeT repeat_cnt = 1);
	ipv4_rator(std::string begin, std::string end,
	           SizeT mix = 0,
	           SizeT repeat_cnt = 1);
	SizeT size() const;

	template<class InIter>
	void blacklist_insert(InIter cidr_begin, InIter cidr_end)
		{ blacklist_.emplace(cidr_begin, cidr_end); }

	class const_iterator
	{
	public:
		const_iterator(const const_iterator& copy);
		const_iterator& operator=(const const_iterator& copy);
		bool operator==(const const_iterator& rhv);
		int32_t operator*();
	private:
	};
	const_iterator get(SizeT n) const;
	const_iterator get_by_val(int32_t val, SizeT repeat_cnt) const;
	const_iterator 
	const_iterator operator[](SizeT n) const;
	const_iterator begin() const;
	const_iterator end() const;
	const array<std::string> DEFAULT_BLACKLIST = {"127.0.0.1/"}

private:
	std::set<cidr_v4> blacklist_;
};

} // namespace

