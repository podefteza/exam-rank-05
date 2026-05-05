#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <string>
#include <iostream>
#include <sstream>

class bigint {
	private:
		std::string _value;
	public:
	bigint();
	bigint(unsigned int value);
	bigint(std::string value);
	bigint(bigint const& rhs);

	bigint& operator=(bigint const& rhs);
	bigint operator+(bigint const& rhs) const;
	bigint& operator+=(bigint const& rhs);
	bigint& operator++(void);
	bigint operator++(int);
	bigint operator<<(int digits) const;
	bigint operator>>(int digits);
	bigint& operator>>=(bigint const& rhs);
	bigint& operator<<=(int digit);
	bigint& operator>>=(int digit);
	bool operator==(bigint const& rhs) const;
	bool operator!=(bigint const& rhs) const;
	bool operator>(bigint const& rhs) const;
	bool operator<(bigint const& rhs) const;
	bool operator<=(bigint const& rhs) const;
	bool operator>=(bigint const& rhs) const;

	friend std::ostream& operator<<(std::ostream& out, bigint const& obj);
};

#endif
