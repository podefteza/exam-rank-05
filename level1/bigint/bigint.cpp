#include "bigint.hpp"

bigint::bigint() : n("0") {

}

bigint::bigint(unsigned long long number) {
	n = std::to_string(number);
}

bigint::bigint(const bigint &copy) : n(copy.n) {

}

bigint &bigint::operator=(const bigint &copy) {
	if (this != &copy)
		n = copy.n;
	return *this;
}

bigint::~bigint() {

}

std::ostream &operator<<(std::ostream &os, const bigint &n) {
	os << n.n;
	return os;
}

/* start from the last digit of both strings;
 * add corresponding digits and carry;
 * build the result from left to right;
 * stop when both numbers are finished and carry is zero*/
bigint bigint::operator+(const bigint &other) const {
	bigint result;
	result.n.clear();

	int carry = 0;
	int i = n.size() - 1;
	int j = other.n.size() - 1;

	while (i >= 0 || j >= 0 || carry != 0) {
		int digit1 = (i >= 0) ? n[i] - '0' : 0;
		int digit2 = (j >= 0) ? other.n[j] - '0' : 0;

		int sum = digit1 + digit2 + carry;
		result.n = char('0' + (sum % 10)) + result.n;
		carry = sum / 10;

		i--;
		j--;
	}
	return result;
}

// call operator+ and assign the result to *this
bigint &bigint::operator+=(const bigint &other) {
	*this = *this + other;
	return *this;
}

// prefix ++x returns the incremented object
bigint &bigint::operator++() {
	*this = *this + bigint(1);
	return *this;
}

// postfix x++ saves a copy first, increments, then returns the old value
bigint bigint::operator++(int) {
	bigint temp = *this;
	++(*this);
	return temp;
}

/* returns a new object with a shifted version of the number
 * left shift by n digits means append n zeros to the end (example: 42 << 3 = 42000) */
bigint bigint::operator<<(unsigned int n) const {
	bigint result = *this;
	for (unsigned int i = 0; i < n; i++) {
		result.n += '0';
	}
	return result;
}

// shifts the number in-place
bigint &bigint::operator<<=(unsigned int n) {
	for (unsigned int i = 0; i < n; i++) {
		this->n += '0';
	}
	return *this;
}

/* returns a new object with a shifted version of the number
 * right shift by n digits means remove n digits from the end. (example: 1337 >> 2 = 13)
 * if the shift is larger than the number length, the result should be 0.*/
bigint bigint::operator>>(unsigned int n) const {
	bigint result = *this;
	if (n >= result.n.size()) {
		result.n = "0";
	} else {
		result.n.erase(result.n.size() - n);
	}
	return result;
}

// shifts the number in-place
bigint &bigint::operator>>=(unsigned int n) {
	if (n >= this->n.size()) {
		this->n = "0";
	} else {
		this->n.erase(this->n.size() - n);
	}
	return *this;
}

bigint bigint::operator<<(const bigint &shift) const {
	unsigned int n = std::stoul(shift.n);
	return *this << n;
}

bigint &bigint::operator<<=(const bigint &shift) {
	unsigned int n = std::stoul(shift.n);
	return *this <<= n;
}

bigint bigint::operator>>(const bigint &shift) const {
	unsigned int n = std::stoul(shift.n);
	return *this >> n;
}

bigint &bigint::operator>>=(const bigint &shift) {
	unsigned int n = std::stoul(shift.n);
	return *this >>= n;
}

bool bigint::operator<(const bigint &other) const {
	if (this->n.size() != other.n.size()) {
		return this->n.size() < other.n.size();
	}
	return this->n < other.n;
}

bool bigint::operator<=(const bigint &other) const {
	return *this < other || *this == other;
}

bool bigint::operator>(const bigint &other) const {
	return other < *this;
}

bool bigint::operator>=(const bigint &other) const {
	return !(*this < other);
}

bool bigint::operator==(const bigint &other) const {
	return this->n == other.n;
}

bool bigint::operator!=(const bigint &other) const {
	return !(this->n == other.n);
}
