#include <ipv4.hpp>

using namespace rators;

TEST(test_ipv4, cidr)
{
	ipv4 loopbacks({"127.0.0.0/24"});
	uint32_t j = ntohl(inet_addr("127.0.0.1"));
	for(auto i : loopbacks)
	{
		EXPECT_EQ (cidr_v4(j, 32), i);
		++j;
	}
}

TEST(test_ipv4, begin_end)
{
	ipv4 addrs({"192.168.1.1"}, {"192.168.1.4"});
	auto i = addrs.begin();
	EXPECT_EQ(cidr_v4("192.168.1.1/32"), *i++);
	EXPECT_EQ(cidr_v4("192.168.1.2/32"), *i++);
	EXPECT_EQ(cidr_v4("192.168.1.3/32"), *i++);
	EXPECT_EQ(cidr_v4("192.168.1.4/32"), *i++);
	EXPECT_EQ(addrs.end(), i);
}

TEST(test_ipv4, cidr_with_blacklist)
{
	
}

TEST(test_ipv4, begin_end_with_blacklist)
{

}
