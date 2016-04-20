/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160407 11:27:23 */

#include <shuffler.hpp>
#include <iostream>

TEST(test_shuffler, int_1_100)
{
	uint8_t ints[100];
	for (uint8_t i = 0; i < 100; ++i)
		ints[i] = i;
	uint8_t produced_ints[100] = {0};
	auto sh = shuffler<uint8_t*>(ints, ints + 100);
	ASSERT_EQ(sh.size(), 100);
	uint8_t counter = 0;
	for (const auto& i : sh)
		produced_ints[counter++] = i;
	std::sort(produced_ints, produced_ints + sizeof(produced_ints));
	for (uint8_t i = 0; i < 100; ++i)
		ASSERT_EQ(i, produced_ints[i]);
}

TEST(test_shuffler, uint16)
{
	uint16_t ints[0x10000];
	for (uint32_t i = 0; i < 0x10000; ++i)
		ints[i] = (uint16_t)i;
	uint32_t produced_ints[0x10000] = {0};
	auto sh = shuffler<uint16_t*>(ints, ints + 0x10000);
	uint32_t counter = 0;
	for (auto i : sh)
		produced_ints[counter++] = i;
	ASSERT_EQ(0x10000, counter);
	std::sort(produced_ints, produced_ints + 0x10000);
	for (uint32_t i = 0; i < 0x10000; ++i)
		ASSERT_EQ(i, produced_ints[i]);
}

TEST(test_shuffler, int_1_100_cycle_3)
{
	uint8_t ints[100];
	for (uint8_t i = 0; i < 100; ++i)
		ints[i] = i;
	std::vector<uint8_t> produced_ints;
	auto sh = shuffler<uint8_t*>(ints, ints + 100, 3);
	ASSERT_EQ(300, sh.size());
	uint8_t counter = 0;
	for (const auto& i : sh)
		produced_ints.emplace_back(i);
	ASSERT_EQ(300, produced_ints.size());
	std::sort(produced_ints.begin(), produced_ints.end());
	for (uint16_t i = 0; i < 300; ++i)
		ASSERT_EQ(i/3, produced_ints[i]);
}

