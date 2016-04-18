#include <ipv4.hpp>
#include <shuffler.hpp>

using namespace rators;

TEST(test_shufipv4, simple)
{
	auto addrs = ipv4({"192.168.1.0/24"});
	auto shufaddrs = shuffler<ipv4::const_iterator>(addrs.begin(), addrs.end());
	std::vector<cidr_v4> oaddrs;
	for (auto i : shufaddrs)
		oaddrs.emplace_back(i);
	ASSERT_EQ(255, shufaddrs.size());
	ASSERT_EQ(255, oaddrs.size());
	std::sort(oaddrs.begin(), oaddrs.end());
	uint32_t iaddr = ntohl(inet_addr("192.168.1.1"));
	for (size_t i = 0; i < 255; ++i)
		EXPECT_EQ(iaddr+i, (uint32_t)oaddrs[i]) << i;
}

