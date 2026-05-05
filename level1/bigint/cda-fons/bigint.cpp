#include "bigint.hpp"

bigint::bigint() : _value("0") {}
bigint::bigint(std::string value) : _value(value) {}
bigint::bigint(unsigned int value)
{
	std::ostringstream ss;
	ss << value;
	this->_value = ss.str();
}

bigint::bigint(bigint const& rhs) : _value(rhs._value) {}

bigint& bigint::operator=(bigint const& rhs)
{
	if (this != &rhs)
		this->_value = rhs._value;
	return (*this);
}

bigint bigint::operator+(bigint const& rhs) const
{
	std::string lhsStr = this->_value;
	std::string rhsStr = rhs._value;

	if (lhsStr.length() > rhsStr.length())
		rhsStr.insert(0, lhsStr.length() - rhsStr.length(), '0');
	else if(lhsStr.length() < rhsStr.length())
		lhsStr.insert(0, rhsStr.length() - lhsStr.length(), '0');

	std::string result;
	int sum = 0;
	int digit = 0;
	int carry = 0;

	for(int i = lhsStr.length() - 1; i >= 0; i--)
	{
		sum = (lhsStr[i] - '0') + (rhsStr[i] - '0') + carry;
		digit = sum % 10;
		carry = sum / 10;
		result.insert(0, 1, digit + '0');
	}
	if (carry)
		result.insert(0, 1, carry + '0');
	return(bigint(result));
}


bigint& bigint::operator+=(bigint const& rhs)
{
	*this = *this + rhs;
	return (*this);
}

bigint& bigint::operator++(void)
{
	return (*this += bigint(1));
}

bigint bigint::operator++(int)
{
	bigint tmp = *this;
	++(*this);
	return(tmp);
}

bigint bigint::operator<<(int digits) const
{
	std::string result = this->_value;
	if (result == "0")
		return (bigint("0"));
	result.append(digits, '0');
	return (bigint(result));
}

bigint bigint::operator>>(int digits)
{
	std::string result = this->_value;
	if (result == "0" || static_cast<size_t>(digits) > result.length())
		return bigint("0");
	result.erase(result.length() - digits);
	return (bigint(result));
}

bigint& bigint::operator<<=(int digits)
{
	*this = (*this << digits);
	return (*this);
}

bigint& bigint::operator>>=(int digits)
{
	*this = (*this >> digits);
	return (*this);
}

bigint& bigint::operator>>=(bigint const& rhs)
{
	int digit = std::atoi(rhs._value.c_str());
	*this = (*this >> digit);
	return (*this);
}

bool bigint::operator==(bigint const& rhs) const
{
	if (this->_value == rhs._value)
		return true;
	return false;
}

bool bigint::operator!=(bigint const& rhs) const
{
	return (!(*this == rhs));
}

bool bigint::operator>(bigint const& rhs) const
{
	std::string lhsStr = this->_value;
	std::string rhsStr = rhs._value;

	if (lhsStr.length() > rhsStr.length())
		return true;
	else if (lhsStr.length() < rhsStr.length())
		return false;
	return (lhsStr > rhsStr);
}

bool bigint::operator<(bigint const& rhs) const
{
	return (!(*this > rhs) && !(*this == rhs));
}

bool bigint::operator<=(bigint const& rhs) const
{
	return ((*this < rhs) || (*this == rhs));
}

bool bigint::operator>=(bigint const& rhs) const
{
	return ((*this > rhs) || (*this == rhs));
}

std::ostream& operator<<(std::ostream& out, bigint const& obj)
{
	out << obj._value;
	return out;
}
