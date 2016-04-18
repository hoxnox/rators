/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160418 15:39:24 */

#include <math.hpp>
#include <sstream>

using namespace rators;

TEST(test_math, gcd)
{
	EXPECT_EQ(1, gcd(1, 2));
	EXPECT_EQ(2, gcd(2, 2));
	EXPECT_EQ(1, gcd(3, 2));
	EXPECT_EQ(3, gcd(3, 3));
	EXPECT_EQ(6, gcd(12, 18));
}

TEST(test_math, is_coprime)
{
	EXPECT_TRUE (is_coprime<1>(1, {2}));
	EXPECT_TRUE (is_coprime<3>(1, {2, 3, 4}));
	EXPECT_TRUE (is_coprime<4>(4, {3, 5, 7, 9}));
	EXPECT_FALSE(is_coprime<7>(2, {1, 3, 5, 7, 9, 11, 4}));
	EXPECT_FALSE(is_coprime<1>(12, {18}));
}

TEST(test_math, is_prime_naive)
{
	EXPECT_TRUE (is_prime_naive(2));
	EXPECT_TRUE (is_prime_naive(3));
	EXPECT_FALSE(is_prime_naive(4));
	EXPECT_TRUE (is_prime_naive(5));
	EXPECT_FALSE(is_prime_naive(6));
	EXPECT_TRUE (is_prime_naive(7));
	EXPECT_FALSE(is_prime_naive(8));
	EXPECT_FALSE(is_prime_naive(9));
	EXPECT_FALSE(is_prime_naive(10));
	EXPECT_TRUE (is_prime_naive(11));
	EXPECT_FALSE(is_prime_naive(12));
}

TEST(test_math, find_ge_prime)
{
	EXPECT_EQ(1, find_ge_prime(0));
	EXPECT_EQ(2, find_ge_prime(2));
	EXPECT_EQ(3, find_ge_prime(3));
	EXPECT_EQ(5, find_ge_prime(4));
	EXPECT_EQ(5, find_ge_prime(5));
	EXPECT_EQ(7, find_ge_prime(6));
	EXPECT_EQ(7, find_ge_prime(7));
	EXPECT_EQ(11,find_ge_prime(8));
	EXPECT_EQ(18446744073709551419UL,find_ge_prime(18446744073709551416UL));
}

// TODO: zero sizes
//TEST(test_math, find_gt_coprime_v0)
//{
//	std::array<bigint_t, 7> etalon({1, 0, 3, 0, 0, 0, 0});
//	std::array<bigint_t, 7> rs = find_gt_coprime(std::array<bigint_t, 7>({1, 0, 3, 0, 0, 0, 0}));
//	EXPECT_EQ(etalon, rs);
//}

TEST(test_math, find_gt_coprime_v1)
{
	std::array<bigint_t, 7> etalon({2, 11, 3, 17, 5, 7, 13});
	std::array<bigint_t, 7> rs = find_gt_coprime(std::array<bigint_t, 7>({2, 6, 3, 8, 4, 5, 7}));
	EXPECT_EQ(etalon, rs);
}

TEST(test_math, find_gt_coprime_v2)
{
	std::array<bigint_t, 7> etalon({4, 11, 23, 17, 5, 7, 13});
	std::array<bigint_t, 7> rs = find_gt_coprime(std::array<bigint_t, 7>({4, 6, 22, 8, 4, 5, 7}));
	EXPECT_EQ(etalon, rs);
}

