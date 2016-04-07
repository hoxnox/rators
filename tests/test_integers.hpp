/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160407 11:27:23 */

#include <integers.hpp>
#include <iostream>


TEST(test_integers, uint16)
{
	auto ints = integers<uint16_t>(0, 0xFFFF);
	uint32_t v = 0;
	for (auto i = ints.begin(); i != ints.end(); ++i)
		ASSERT_EQ(v++, *i);
	ASSERT_EQ(v, 0x10000);
}

TEST(test_integers, int_0_99)
{
	auto ints = integers<uint8_t>(0, 99);
	uint8_t v = 0;
	for (auto i : ints)
		ASSERT_EQ(v++, i);
	ASSERT_EQ(v, 100);
}

