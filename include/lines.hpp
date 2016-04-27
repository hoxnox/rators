/**@author hoxnox <hoxnox@gmail.com>
 * @date 20160427 13:49:37*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace rators {

class lines
{
public:
	class const_iterator;
	lines(std::string filename, size_t count) : fname_(filename), count_(count) {}
	const_iterator begin() const;
	const_iterator end() const;

private:
	std::string fname_;
	const size_t count_;

friend class lines::const_iterator;
};

class lines::const_iterator 
	: public std::iterator<std::input_iterator_tag, std::string, bigint_t>
{
public:
	const_iterator() {};
	const_iterator(const const_iterator& copy) { operator=(copy); };
	const_iterator& operator=(const const_iterator& copy);
	bool            operator==(const const_iterator& rhv) const;
	bool            operator!=(const const_iterator& rhv) const { return !operator==(rhv); }
	const_iterator& operator++();
	const_iterator  operator++(int);
	const_iterator& operator+=(bigint_t n);
	const_iterator  operator+(bigint_t n);
	std::string     operator*() const;
	bigint_t        distance(const const_iterator& rhv) const
	{
		if (rhv.lineno_ < lineno_)
			return 0;
		return rhv.lineno_ - lineno_;
	}

private:
	std::unique_ptr<std::ifstream> fstream_{nullptr};
	std::string   line_;
	bigint_t      lineno_{0};
	const lines*  owner_{nullptr};

friend class lines;
};

lines::const_iterator
lines::begin() const
{
	const_iterator rs;
	rs.owner_ = this;
	rs.fstream_.reset(new std::ifstream(fname_));
	std::getline(*rs.fstream_, rs.line_);
	if (rs.line_.empty() && rs.fstream_->eof())
		return end();
	rs.lineno_= 0;
	return rs;
}

lines::const_iterator
lines::end() const
{
	const_iterator rs;
	rs.owner_ = this;
	rs.fstream_.reset(new std::ifstream(fname_));
	rs.fstream_->seekg(0, std::ios::end);
	rs.lineno_ = count_;
	return rs;
}

lines::const_iterator&
lines::const_iterator::operator=(const const_iterator& copy)
{
	owner_ = copy.owner_;
	if (!owner_)
		return *this;
	fstream_.reset(new std::ifstream(copy.owner_->fname_));
	lineno_ = copy.lineno_;
	if (lineno_ >= owner_->count_)
		return *this;
	for (auto i = 0; i <= lineno_; ++i)
	{
		line_.clear();
		std::getline(*fstream_, line_);
		if (line_.empty() && fstream_->eof())
		{
			*this = owner_->end();
			return *this;
		}
	}
	return *this;
}

bool
lines::const_iterator::operator==(const const_iterator& rhv) const
{
	if (owner_ != rhv.owner_)
		return false;
	if (lineno_ != rhv.lineno_)
		return false;
	return true;
}

lines::const_iterator&
lines::const_iterator::operator++()
{
	if (!owner_)
		return *this;
	if (lineno_ >= owner_->count_)
		return *this;
	line_.clear();
	std::getline(*fstream_, line_);
	if (line_.empty() && fstream_->eof())
	{
		*this = owner_->end();
		return *this;
	}
	++lineno_;
	return *this;
}

lines::const_iterator 
lines::const_iterator::operator++(int)
{
	const_iterator prev = *this;
	operator++();
	return prev;
}

lines::const_iterator&
lines::const_iterator::operator+=(bigint_t n)
{
	if (!owner_ || lineno_ >= owner_->count_ || !fstream_->good())
	{
		*this = owner_->end();
		return *this;
	}
	for(bigint_t i = 0; i < n && operator!=(owner_->end()); ++i)
	{
		line_.clear();
		std::getline(*fstream_, line_);
		if (line_.empty() && fstream_->eof())
		{
			*this = owner_->end();
			return *this;
		}
		++lineno_;
	}
	return *this;
}

lines::const_iterator
lines::const_iterator::operator+(bigint_t n)
{
	const_iterator rs(*this);
	rs += n;
	return rs;
}

std::string
lines::const_iterator::operator*() const
{
	return line_;
}

} // namespace

namespace std {

typename iterator_traits<rators::lines::const_iterator>::difference_type
distance(const rators::lines::const_iterator& first, const rators::lines::const_iterator& last)
{
	return first.distance(last);
}

} // namespace
