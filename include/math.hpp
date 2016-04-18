/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160418 15:39:24 */

#pragma once
#include <rators_config.h>

namespace rators {

bigint_t
gcd(bigint_t a, bigint_t b)
{
	return (!b ? a : gcd(b, a%b));
}

template<std::size_t N> bool
is_coprime(bigint_t val, const std::array<bigint_t, N>& arr)
{
	bigint_t mt = 1;
	for (const auto& i : arr)
		mt *= i;
	if (gcd(val, mt) == 1)
		return true;
	return false;
}

/**@brief Simple prime criteria*/
inline bool
is_prime_naive(bigint_t n)
{
	int i,root;
	if (n < 4 && n > 0)
		return true;
	if (n%2 == 0 || n%3 == 0)
		return false;
	root = (bigint_t)sqrt(n);
	for (i=5; i<=root; i+=6)
	{
		if (n%i == 0)
			return false;
	}
	for (i=7; i<=root; i+=6)
	{
		if (n%i == 0)
			return false;
	}
	return true;
}

/**@brief Find the prime number greater or equal to the given*/
inline bigint_t
find_ge_prime(bigint_t n)
{
	bigint_t i = n;
	while (1)
	{
		if (is_prime_naive(i))
			break;
		i++;
	}
	return i;
}

/**@brief Find co-prime numbers, that is greater or equal to the given.
 *
 * This algorithm doesn't give the closest vector, but is very simple.*/
template<std::size_t N> std::array<bigint_t, N>
find_gt_coprime(const std::array<bigint_t, N>& arr)
{
	if (arr.empty())
		return std::array<bigint_t, N>();
	std::vector<std::pair<bigint_t, bigint_t>> svec;
	for (bigint_t i = 0; i < arr.size(); ++i)
		svec.emplace_back(std::make_pair(i, arr[i]));
	std::sort(svec.begin(), svec.end(),
			[](std::pair<bigint_t, bigint_t> a, std::pair<bigint_t, bigint_t> b)
			{ return a.second < b.second; });
	std::array<bigint_t, N> result;
	result[svec[0].first] = svec[0].second;
	bigint_t prev = svec[0].second;
	for (bigint_t i = 1; i < svec.size(); ++i)
	{
		bigint_t curr = find_ge_prime(svec[i].second);
		if (prev > 0 && curr <= prev)
			curr = find_ge_prime(prev + 1);
		result[svec[i].first] = curr;
		prev = curr;
	}
	return result;
}

} // namespace

namespace std {

template<std::size_t N>
ostream& operator<<(ostream& os, const array<bigint_t, N>& arr)
{
	os << "{";
	std::string delim;
	for (const auto& i : arr)
	{
		os << delim << i;
		delim = ",";
	}
	os << "}";
	return os;
}

} // namespace 

