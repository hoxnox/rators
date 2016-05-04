/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160420 09:11:52 */

#include <mixed_product.hpp>
#include <shuffler.hpp>
#include <unordered_set>
#include <lines.hpp>

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
	ASSERT_EQ(10, std::distance(ipr1.begin(), ipr1.end()));
	ipv4 ipr2({"127.0.255.253"}, {"127.1.0.2"});
	ASSERT_EQ(6, std::distance(ipr2.begin(), ipr2.end()));
	using ip_mixer = mixed_product<typename ipv4::const_iterator, 2>;
	auto mixer = ip_mixer({ip_mixer::range_t(ipr1.begin(), ipr1.end()),
	                       ip_mixer::range_t(ipr2.begin(), ipr2.end())});
	std::stringstream ss;
	for (const auto& i : mixer)
		ss << i;
	ASSERT_EQ("{192.168.10.4, 127.1.0.1}"
	          "{192.168.10.5, 127.1.0.2}"
	          "{192.168.10.6, 127.0.255.253}"
	          "{192.168.10.7, 127.0.255.254}"
	          "{192.168.10.8, 127.0.255.255}"
	          "{192.168.10.9, 127.1.0.0}"
	          "{192.168.10.10, 127.1.0.1}"
	          "{192.168.10.1, 127.0.255.253}"
	          "{192.168.10.2, 127.0.255.254}"
	          "{192.168.10.3, 127.0.255.255}"
	          "{192.168.10.4, 127.1.0.0}"
	          "{192.168.10.5, 127.1.0.1}"
	          "{192.168.10.6, 127.1.0.2}"
	          "{192.168.10.7, 127.0.255.253}"
	          "{192.168.10.8, 127.0.255.254}"
	          "{192.168.10.9, 127.0.255.255}"
	          "{192.168.10.10, 127.1.0.0}"
	          "{192.168.10.1, 127.1.0.2}"
	          "{192.168.10.2, 127.0.255.253}"
	          "{192.168.10.3, 127.0.255.254}"
	          "{192.168.10.4, 127.0.255.255}"
	          "{192.168.10.5, 127.1.0.0}"
	          "{192.168.10.6, 127.1.0.1}"
	          "{192.168.10.7, 127.1.0.2}"
	          "{192.168.10.8, 127.0.255.253}"
	          "{192.168.10.9, 127.0.255.254}"
	          "{192.168.10.10, 127.0.255.255}"
	          "{192.168.10.1, 127.1.0.1}"
	          "{192.168.10.2, 127.1.0.2}"
	          "{192.168.10.3, 127.0.255.253}"
	          "{192.168.10.4, 127.0.255.254}"
	          "{192.168.10.5, 127.0.255.255}"
	          "{192.168.10.6, 127.1.0.0}"
	          "{192.168.10.7, 127.1.0.1}"
	          "{192.168.10.8, 127.1.0.2}"
	          "{192.168.10.9, 127.0.255.253}"
	          "{192.168.10.10, 127.0.255.254}"
	          "{192.168.10.1, 127.1.0.0}"
	          "{192.168.10.2, 127.1.0.1}"
	          "{192.168.10.3, 127.1.0.2}"
	          "{192.168.10.4, 127.0.255.253}"
	          "{192.168.10.5, 127.0.255.254}"
	          "{192.168.10.6, 127.0.255.255}"
	          "{192.168.10.7, 127.1.0.0}"
	          "{192.168.10.8, 127.1.0.1}"
	          "{192.168.10.9, 127.1.0.2}"
	          "{192.168.10.10, 127.0.255.253}"
	          "{192.168.10.1, 127.0.255.255}"
	          "{192.168.10.2, 127.1.0.0}"
	          "{192.168.10.3, 127.1.0.1}"
	          "{192.168.10.4, 127.1.0.2}"
	          "{192.168.10.5, 127.0.255.253}"
	          "{192.168.10.6, 127.0.255.254}"
	          "{192.168.10.7, 127.0.255.255}"
	          "{192.168.10.8, 127.1.0.0}"
	          "{192.168.10.9, 127.1.0.1}"
	          "{192.168.10.10, 127.1.0.2}"
	          "{192.168.10.1, 127.0.255.254}"
	          "{192.168.10.2, 127.0.255.255}"
	          "{192.168.10.3, 127.1.0.0}", ss.str());
}

TEST_F(test_mixed_product, big_ipv4)
{
	ipv4 ipr1({"1.0.0.1"}, {"223.255.255.255"});
	ASSERT_EQ(3741319167, std::distance(ipr1.begin(), ipr1.end()));
	using ip_mixer = mixed_product<typename ipv4::const_iterator, 1>;
	auto mixer = ip_mixer({ip_mixer::range_t(ipr1.begin(), ipr1.end())});
	//ASSERT_EQ(1, mixer.size());
}

TEST_F(test_mixed_product, lines)
{
	const std::string filename_tpl{"/tmp/rators_test_XXXXXX"};
	std::unique_ptr<char>(file1name);
	std::unique_ptr<char>(file2name);
	std::stringstream file1content;
	std::stringstream file2content;
	file1name.reset(new char[filename_tpl.length()]);
	file2name.reset(new char[filename_tpl.length()]);
	std::copy(filename_tpl.begin(), filename_tpl.end(), file1name.get());
	std::copy(filename_tpl.begin(), filename_tpl.end(), file2name.get());
	file1content << std::endl << "file1 line2"
	             << std::endl << "file1 line3"
	             << std::endl << "file1 line4"
	             << std::endl
	             << std::endl << "file1 line6"
	             << std::endl << "file1 line7";
	file2content << std::endl << "file2 line1"
	             << std::endl << "line2 line2";
	int fd1 = mkstemp(file1name.get());
	int fd2 = mkstemp(file2name.get());
	ASSERT_NE(-1, fd1);
	ASSERT_NE(-1, fd2);
	ASSERT_EQ(file1content.str().length(),
		write(fd1, file1content.str().c_str(), file1content.str().length()));
	ASSERT_EQ(file2content.str().length(),
		write(fd2, file2content.str().c_str(), file2content.str().length()));
	close(fd1);
	close(fd2);

	lines f1(file1name.get(), 7);
	lines f2(file2name.get(), 2);
	ASSERT_EQ(7, std::distance(f1.begin(), f1.end()));
	ASSERT_EQ(2, std::distance(f1.begin(), f2.end()));
	using mixer_t = mixed_product<typename lines::const_iterator, 2>;
	auto mixer = mixer_t({mixer_t::range_t(f1.begin(), f1.end()),
	                      mixer_t::range_t(f2.begin(), f2.end())});
	std::stringstream ss;
	for (auto i : mixer)
		ss << i << std::endl;
	remove(file1name.get());
	remove(file2name.get());
	ASSERT_EQ("{, }\n"
	          "{file1 line6, file2 line1}\n"
	          "{file1 line7, }\n"
	          "{, file2 line1}\n"
	          "{file1 line2, }\n"
	          "{file1 line3, file2 line1}\n"
	          "{file1 line4, }\n"
	          "{, file2 line1}\n"
	          "{file1 line6, }\n"
	          "{file1 line7, file2 line1}\n"
	          "{, }\n"
	          "{file1 line2, file2 line1}\n"
	          "{file1 line3, }\n"
	          "{file1 line4, file2 line1}\n"
		, ss.str());
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

