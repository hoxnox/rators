/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160407 11:27:23 */

#include <integers.hpp>
#include <iostream>


TEST(test_integers, uint16)
{
	auto ints = integers<uint16_t>(0, 0xFFFF);
	ASSERT_EQ(0x10000, ints.size());
	uint32_t v = 0;
	for (auto i = ints.begin(); i != ints.end(); ++i)
		ASSERT_EQ(v++, *i);
	ASSERT_EQ(v, 0x10000);
}

TEST(test_integers, int_0_99)
{
	auto ints = integers<uint8_t>(0, 99);
	ASSERT_EQ(100, ints.size());
	uint8_t v = 0;
	for (auto i : ints)
		ASSERT_EQ(v++, i);
	ASSERT_EQ(v, 100);
}

TEST(test_integers, get)
{
	auto ints = integers<uint8_t>(0, 99);
	ASSERT_EQ(100, ints.size());
	uint8_t v = 50;
	for (auto pos = ints.get(50); pos != ints.end(); ++pos)
		ASSERT_EQ(v++, *pos);
	ASSERT_EQ(v, 100);
}

TEST(test_integers, operator_ppn)
{
	auto ints = integers<uint8_t>(0, 99);
	ASSERT_EQ(100, ints.size());
	auto pos = ints.begin();
	pos += 10;
	EXPECT_EQ(10, *pos);
	pos += 5;
	EXPECT_EQ(15, *pos);
	pos += 100;
	EXPECT_EQ(ints.end(), pos);
}

