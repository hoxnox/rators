/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160405 11:39:23 */

#include <ipv4_rator.hpp>

using namespace rators;

class test_ipv4_rator : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
};

TEST_F(test_ipv4_rator, general)
{
	ipv4_rator ipv4();
}

