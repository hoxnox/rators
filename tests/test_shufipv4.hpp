#include <ipv4.hpp>
#include <shuffler.hpp>

using namespace rators;

TEST(test_shufipv4, simple)
{
	auto addrs = ipv4({"192.168.1.0/24"});
	auto shufaddrs = shuffler<ipv4::const_iterator>(addrs.begin(), addrs.end());
	for (auto i : shufaddrs)
		std::cout << i << std::endl;
}

