/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160405 11:39:23
 *
 * @brief rators test launcher.*/

// Google Testing Framework
#include <gtest/gtest.h>

// test cases
#include "test_cidr_v4.hpp"
#include "test_shuffler.hpp"
#include "test_integers.hpp"
#include "test_ipv4.hpp"
#include "test_lpfst.hpp"
#include "test_shufipv4.hpp"

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


