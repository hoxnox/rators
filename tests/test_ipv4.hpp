#include <ipv4.hpp>

using namespace rators;

TEST(test_ipv4, cidr)
{
	ipv4 loopbacks({"127.0.0.0/24"});
	ASSERT_EQ(0xFF, loopbacks.size());
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
	ASSERT_EQ(4, addrs.size());
	auto i = addrs.begin();
	EXPECT_EQ(cidr_v4("192.168.1.1/32"), *i++);
	EXPECT_EQ(cidr_v4("192.168.1.2/32"), *i++);
	EXPECT_EQ(cidr_v4("192.168.1.3/32"), *i++);
	EXPECT_EQ(cidr_v4("192.168.1.4/32"), *i++);
	//EXPECT_EQ(addrs.end(), i);
}

TEST(test_ipv4, get)
{
	ipv4 addrs({"23.16.4.0/26"});
	ASSERT_EQ(63, addrs.size());
	uint32_t j = ntohl(inet_addr("23.16.4.8"));
	for(auto pos = addrs.get({"23.16.4.8"}); pos != addrs.end(); ++pos)
	{
		EXPECT_EQ (cidr_v4(j, 32), *pos);
		++j;
	}
	ASSERT_EQ(cidr_v4("23.16.4.64/32"), cidr_v4(j, 32));
}

TEST(test_ipv4, operator_ppn)
{
	ipv4 addrs({"3.0.0.0/8"});
	ASSERT_EQ(0xffffff, addrs.size());
	auto pos = addrs.begin();
	EXPECT_EQ(cidr_v4("3.0.0.1"), *pos);
	pos += 4;
	EXPECT_EQ(cidr_v4("3.0.0.5"), *pos);
	pos += 250;
	EXPECT_EQ(cidr_v4("3.0.0.255"), *pos);
	pos += 1;
	EXPECT_EQ(cidr_v4("3.0.1.0"), *pos);
}

TEST(test_ipv4, cidr_with_blacklist)
{
	ipv4 addrs({"222.0.0.0/24"});
	ASSERT_EQ(0xFF, addrs.size());
	addrs.append_to_blacklist({"222.0.0.0/29"});
	uint32_t j = ntohl(inet_addr("222.0.0.8"));
	for(auto i : addrs)
	{
		EXPECT_EQ (cidr_v4(j, 32), i);
		++j;
	}
}

TEST(test_ipv4, begin_end_with_blacklist)
{
	ipv4 addrs({"1.168.1.1"}, {"1.168.1.4"});
	ASSERT_EQ(4, addrs.size());
	addrs.append_to_blacklist({"1.168.1.2/32"});
	auto i = addrs.begin();
	EXPECT_EQ(cidr_v4("1.168.1.1/32"), *i++);
	EXPECT_EQ(cidr_v4("1.168.1.3/32"), *i++);
	EXPECT_EQ(cidr_v4("1.168.1.4/32"), *i++);
	//EXPECT_EQ(addrs.end(), i);
}

TEST(test_ipv4, get_with_blacklist)
{
	ipv4 addrs({"21.8.252.0/22"});
	addrs.append_to_blacklist({"21.8.253.0/24"});
	ASSERT_EQ(1023, addrs.size());
	uint32_t j = ntohl(inet_addr("21.8.252.223"));
	for(auto pos = addrs.get({"21.8.252.223"}); pos != addrs.end(); ++pos)
	{
		EXPECT_EQ (cidr_v4(j, 32), *pos);
		if (j == ntohl(inet_addr("21.8.252.255")))
			j += 0x101;
		else	
			++j;
	}
	ASSERT_EQ(cidr_v4("21.9.0.0/32"), cidr_v4(j, 32));
}

