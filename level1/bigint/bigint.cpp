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

bigint &bigint::operator+=(const bigint &other) {
	*this = *this + other;
	return *this;
}

bigint &bigint::operator++() {
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int) {
	bigint temp = *this;
	++(*this);
	return temp;
}

bigint bigint::operator<<(unsigned int n) const {
	bigint result = *this;
	for (unsigned int i = 0; i < n; i++) {
		result.n += '0';
	}
	return result;
}

bigint &bigint::operator<<=(unsigned int n) {
	for (unsigned int i = 0; i < n; i++) {
		this->n += '0';
	}
	return *this;
}

bigint bigint::operator>>(unsigned int n) const {
	bigint result = *this;
	if (n >= result.n.size()) {
		result.n = "0";
	} else {
		result.n.erase(result.n.size() - n);
	}
	return result;
}

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
