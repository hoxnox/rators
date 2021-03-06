/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160418 15:39:24 */

#include <cyclic_group.hpp>
#include <sstream>

using namespace rators;

TEST(test_cyclic_group, general)
{
	cyclic_group<3> gr({4, 6, 5}, 0x1234);
	ASSERT_EQ(4*6*5, gr.size());
	std::stringstream ss;
	for (auto i : gr)
		ss << i << ';';
	const std::string etalon = 
		"{2,0,2};{3,1,3};{0,2,4};{1,3,0};{2,4,1};{3,5,2};{1,0,4};"
		"{2,1,0};{3,2,1};{0,3,2};{1,4,3};{2,5,4};{0,0,1};{1,1,2};"
		"{2,2,3};{3,3,4};{0,4,0};{1,5,1};{3,0,3};{0,1,4};{1,2,0};"
		"{2,3,1};{3,4,2};{0,5,3};{2,0,0};{3,1,1};{0,2,2};{1,3,3};"
		"{2,4,4};{3,5,0};{1,0,2};{2,1,3};{3,2,4};{0,3,0};{1,4,1};"
		"{2,5,2};{0,0,4};{1,1,0};{2,2,1};{3,3,2};{0,4,3};{1,5,4};"
		"{3,0,1};{0,1,2};{1,2,3};{2,3,4};{3,4,0};{0,5,1};{2,0,3};"
		"{3,1,4};{0,2,0};{1,3,1};{2,4,2};{3,5,3};{1,0,0};{2,1,1};"
		"{3,2,2};{0,3,3};{1,4,4};{2,5,0};{0,0,2};{1,1,3};{2,2,4};"
		"{3,3,0};{0,4,1};{1,5,2};{3,0,4};{0,1,0};{1,2,1};{2,3,2};"
		"{3,4,3};{0,5,4};{2,0,1};{3,1,2};{0,2,3};{1,3,4};{2,4,0};"
		"{3,5,1};{1,0,3};{2,1,4};{3,2,0};{0,3,1};{1,4,2};{2,5,3};"
		"{0,0,0};{1,1,1};{2,2,2};{3,3,3};{0,4,4};{1,5,0};{3,0,2};"
		"{0,1,3};{1,2,4};{2,3,0};{3,4,1};{0,5,2};{2,0,4};{3,1,0};"
		"{0,2,1};{1,3,2};{2,4,3};{3,5,4};{1,0,1};{2,1,2};{3,2,3};"
		"{0,3,4};{1,4,0};{2,5,1};{0,0,3};{1,1,4};{2,2,0};{3,3,1};"
		"{0,4,2};{1,5,3};{3,0,0};{0,1,1};{1,2,2};{2,3,3};{3,4,4};"
		"{0,5,0};";
	EXPECT_EQ(etalon, ss.str());
}

TEST(test_cyclic_group, get_by_state)
{
	cyclic_group<3> gr({4, 6, 3}, 0x1234);
	ASSERT_EQ(4*6*3, gr.size());
	std::stringstream ss;
	for (auto i = gr.get_by_state({2,5,2}); i != gr.end(); ++i)
		ss << *i << ';';
	const std::string etalon = 
		"{2,5,2};{0,1,2};{1,2,0};{2,3,1};{3,4,2};{1,0,2};{2,1,0};"
		"{3,2,1};{0,4,0};{1,5,1};{3,0,0};{0,2,2};{1,3,0};{2,4,1};"
		"{3,5,2};{0,0,1};{1,1,2};{2,2,0};{3,3,1};{0,5,0};{2,0,2};"
		"{3,1,0};{0,3,2};{1,4,0};{2,5,1};{0,1,1};{1,2,2};{2,3,0};"
		"{3,4,1};{1,0,1};{2,1,2};{3,2,0};{0,4,2};{1,5,0};{3,0,2};"
		"{0,2,1};{1,3,2};{2,4,0};{3,5,1};{0,0,0};{1,1,1};{2,2,2};"
		"{3,3,0};{0,5,2};{2,0,1};{3,1,2};{0,3,1};{1,4,2};{2,5,0};"
		"{0,1,0};{1,2,1};{2,3,2};{3,4,0};{1,0,0};{2,1,1};{3,2,2};"
		"{0,4,1};{1,5,2};{3,0,1};{0,2,0};{1,3,1};{2,4,2};{3,5,0};"
		"{0,0,2};{1,1,0};{2,2,1};{3,3,2};{0,5,1};";
	EXPECT_EQ(etalon, ss.str());
}

