#include <unistd.h>
#include <algorithm>
#include <lines.hpp>

class test_lines : public ::testing::Test
{
protected:
	void SetUp()
	{
		filename.reset(new char[filename_tpl.length()]);
		std::copy(filename_tpl.begin(), filename_tpl.end(), filename.get());
		filecontent << std::endl << "line2"
		            << std::endl << "line3"
		            << std::endl << "line4"
		            << std::endl
		            << std::endl << "line6"
		            << std::endl << "line7";
		int fd = mkstemp(filename.get());
		ASSERT_NE(-1, fd);
		ASSERT_EQ(filecontent.str().length(),
			write(fd, filecontent.str().c_str(), filecontent.str().length()));
		close(fd);
	}
	void TearDown()
	{
		remove(filename.get());
	}
	const std::string filename_tpl{"/tmp/rators_test_XXXXXX"};
	std::unique_ptr<char>(filename);
	std::stringstream filecontent;
};

TEST_F(test_lines, general)
{
	rators::lines lns(filename.get(), 6);
	std::stringstream ss;
	std::string delim;
	for (auto i : lns)
	{
		ss << delim << i;
		delim = '\n';
	}
	ASSERT_EQ(filecontent.str().substr(0, ss.str().length()), ss.str());
}

TEST_F(test_lines, operator_pn)
{
	rators::lines lns(filename.get(), 6);
	auto pos = lns.begin();
	pos += 2;
	ASSERT_EQ("line3", *pos);
	pos += 4;
	ASSERT_TRUE(pos == lns.end());
}

TEST_F(test_lines, operator_post_pp)
{
	rators::lines lns(filename.get(), 6);
	auto pos = lns.begin();
	ASSERT_EQ("", *pos++);
	ASSERT_EQ("line2", *pos++);
	ASSERT_EQ("line3", *pos++);
	ASSERT_EQ("line4", *pos++);
	ASSERT_EQ("", *pos++);
	ASSERT_EQ("line6", *pos++);
	ASSERT_TRUE(pos++ == lns.end());
	ASSERT_TRUE(pos++ == lns.end());
	ASSERT_TRUE(pos++ == lns.end());
}

TEST_F(test_lines, operator_plus)
{
	rators::lines lns(filename.get(), 6);
	auto pos = lns.begin();
	auto pos2 = pos + 2;
	ASSERT_EQ("", *pos);
	ASSERT_EQ("line3", *pos2);
	++pos;
	ASSERT_EQ("line2", *pos);
	ASSERT_EQ("line3", *pos2);
	pos += 10;
	ASSERT_TRUE(pos == lns.end());
	ASSERT_EQ("line3", *pos2);
	pos2 += 5;
	ASSERT_TRUE(pos == lns.end());
	ASSERT_TRUE(pos2 == lns.end());
}

TEST_F(test_lines, normal_cont_estimate)
{
	rators::lines lns(filename.get(), 7);
	std::stringstream ss;
	std::string delim;
	for (auto i : lns)
	{
		ss << delim << i;
		delim = '\n';
	}
	ASSERT_EQ(filecontent.str(), ss.str());
}

TEST_F(test_lines, bigger_count_estimmate)
{
	rators::lines lns(filename.get(), 10);
	std::stringstream ss;
	std::string delim;
	for (auto i : lns)
	{
		ss << delim << i;
		delim = '\n';
	}
	ASSERT_EQ(filecontent.str(), ss.str());
}

