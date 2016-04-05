/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160405 11:39:23 */

#include <ipv4_rator.hpp>

namespace rators {

IPv4Rator(std::string cidr = "0.0.0.0/0",
          SizeT mix = 0,
          SizeT repeat_cnt = 1,
          bool skip_private = true)
{
}

IPv4Rator(std::string begin, std::string end,
          SizeT mix = 0,
          SizeT repeat_cnt = 1,
          bool skip_private = true)
{
}

SizeT
size() const
{
}

const_iterator(const const_iterator& copy)
{
}
const_iterator(SizeT n);
const_iterator(int32_t val);
const_iterator& operator=(const const_iterator& copy);
bool operator==(const const_iterator& rhv);
int32_t operator*();
const_iterator get(SizeT n) const;
const_iterator operator[](SizeT n) const;
const_iterator begin() const;
const_iterator end() const;

} // namespace

