/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160405 11:39:23
 *
 * @brief rators test launcher.*/

// Google Testing Framework
#include <gtest/gtest.h>

// test cases
//#include <test_ipv4_rator.hpp>
#include "test_cidr_v4.hpp"

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


