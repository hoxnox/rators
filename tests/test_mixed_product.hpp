/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160420 09:11:52 */

#include <mixed_product.hpp>
#include <shuffler.hpp>
#include <unordered_set>

using namespace rators;

class Hash
{
public:
	size_t operator()(const std::array<std::string, 3>& arr) const
	{
		std::hash<std::string> hasher;
		return (hasher(arr[0])<<2)^
		       (hasher(arr[1])<<2)^
		        hasher(arr[2]);
	}
};

class test_mixed_product : public ::testing::Test
{
protected:
	static std::unordered_set<std::array<std::string,3>, Hash> etalon;
	static std::vector<std::string> veg;
	static std::vector<std::string> fru;
	static std::vector<std::string> act;
};


namespace std {
	ostream& operator<<(ostream& os, const std::array<std::string, 3>& val)
	{
		os << "{" << val[0] << ", " << val[1] << ", " << val[2] << "}";
		return os;
	}
} // namespace

TEST_F(test_mixed_product, general)
{
	using str_mixer = mixed_product<std::vector<std::string>::const_iterator, 3>;
	auto mixer = str_mixer({str_mixer::range_t(veg.begin(), veg.end()),
	                        str_mixer::range_t(fru.begin(), fru.end()),
	                        str_mixer::range_t(act.begin(), act.end())});
	std::unordered_set<std::array<std::string,3>, Hash> product;
	for (auto i : mixer)
		product.insert(i);
	ASSERT_EQ(4*6*3, product.size());
	ASSERT_EQ(etalon, product);
}

TEST_F(test_mixed_product, shuffler)
{
	auto sveg = shuffler<std::vector<std::string>::const_iterator>(veg.begin(), veg.end());
	auto sfru = shuffler<std::vector<std::string>::const_iterator>(fru.begin(), fru.end());
	auto sact = shuffler<std::vector<std::string>::const_iterator>(act.begin(), act.end());
	using str_mixer = mixed_product<typename shuffler<std::vector<std::string>::const_iterator>::const_iterator, 3>;
	auto mixer = str_mixer({str_mixer::range_t(sveg.begin(), sveg.end()),
	                        str_mixer::range_t(sfru.begin(), sfru.end()),
	                        str_mixer::range_t(sact.begin(), sact.end())});
	std::unordered_set<std::array<std::string,3>, Hash> product;
	for (auto i : mixer)
		product.insert(i);
	ASSERT_EQ(4*6*3, product.size());
	ASSERT_EQ(etalon, product);
}

namespace std {
	ostream& operator<<(ostream& os, const std::array<std::string, 2>& val)
	{
		os << "{" << val[0] << ", " << val[1] << "}";
		return os;
	}
} // namespace

TEST_F(test_mixed_product, ipv4)
{
	ipv4 ipr1({"192.168.10.1"}, {"192.168.10.10"});
	ipv4 ipr2({"127.0.0.1"}, {"127.0.0.10"});
	using ip_mixer = mixed_product<typename ipv4::const_iterator, 2>;
	auto mixer = ip_mixer({ip_mixer::range_t(ipr1.begin(), ipr1.end()),
	                       ip_mixer::range_t(ipr2.begin(), ipr2.end())});
	for (const auto& i : mixer)
		std::cout << i << std::endl;
}

std::vector<std::string> test_mixed_product::veg({"potato", "carrot", "tomato", "pumpkin"});
std::vector<std::string> test_mixed_product::fru({"apple", "banana", "peach", "orange", "cocos", "grenade"});
std::vector<std::string> test_mixed_product::act({"boil", "fry", "dry"});
std::unordered_set<std::array<std::string,3>, Hash> test_mixed_product::etalon({
	{"carrot", "apple", "boil"},
	{"carrot", "apple", "dry"},
	{"carrot", "apple", "fry"},
	{"carrot", "banana", "boil"},
	{"carrot", "banana", "dry"},
	{"carrot", "banana", "fry"},
	{"carrot", "cocos", "boil"},
	{"carrot", "cocos", "dry"},
	{"carrot", "cocos", "fry"},
	{"carrot", "grenade", "boil"},
	{"carrot", "grenade", "dry"},
	{"carrot", "grenade", "fry"},
	{"carrot", "orange", "boil"},
	{"carrot", "orange", "dry"},
	{"carrot", "orange", "fry"},
	{"carrot", "peach", "boil"},
	{"carrot", "peach", "dry"},
	{"carrot", "peach", "fry"},
	{"potato", "apple", "boil"},
	{"potato", "apple", "dry"},
	{"potato", "apple", "fry"},
	{"potato", "banana", "boil"},
	{"potato", "banana", "dry"},
	{"potato", "banana", "fry"},
	{"potato", "cocos", "boil"},
	{"potato", "cocos", "dry"},
	{"potato", "cocos", "fry"},
	{"potato", "grenade", "boil"},
	{"potato", "grenade", "dry"},
	{"potato", "grenade", "fry"},
	{"potato", "orange", "boil"},
	{"potato", "orange", "dry"},
	{"potato", "orange", "fry"},
	{"potato", "peach", "boil"},
	{"potato", "peach", "dry"},
	{"potato", "peach", "fry"},
	{"pumpkin", "apple", "boil"},
	{"pumpkin", "apple", "dry"},
	{"pumpkin", "apple", "fry"},
	{"pumpkin", "banana", "boil"},
	{"pumpkin", "banana", "dry"},
	{"pumpkin", "banana", "fry"},
	{"pumpkin", "cocos", "boil"},
	{"pumpkin", "cocos", "dry"},
	{"pumpkin", "cocos", "fry"},
	{"pumpkin", "grenade", "boil"},
	{"pumpkin", "grenade", "dry"},
	{"pumpkin", "grenade", "fry"},
	{"pumpkin", "orange", "boil"},
	{"pumpkin", "orange", "dry"},
	{"pumpkin", "orange", "fry"},
	{"pumpkin", "peach", "boil"},
	{"pumpkin", "peach", "dry"},
	{"pumpkin", "peach", "fry"},
	{"tomato", "apple", "boil"},
	{"tomato", "apple", "dry"},
	{"tomato", "apple", "fry"},
	{"tomato", "banana", "boil"},
	{"tomato", "banana", "dry"},
	{"tomato", "banana", "fry"},
	{"tomato", "cocos", "boil"},
	{"tomato", "cocos", "dry"},
	{"tomato", "cocos", "fry"},
	{"tomato", "grenade", "boil"},
	{"tomato", "grenade", "dry"},
	{"tomato", "grenade", "fry"},
	{"tomato", "orange", "boil"},
	{"tomato", "orange", "dry"},
	{"tomato", "orange", "fry"},
	{"tomato", "peach", "boil"},
	{"tomato", "peach", "dry"},
	{"tomato", "peach", "fry"}
});

