#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
	private:
		std::string n;

	public:
		bigint();
		bigint(unsigned long long number);
		bigint(const bigint &copy);
		bigint &operator=(const bigint &copy);
		~bigint();

		friend std::ostream &operator<<(std::ostream &os, const bigint &n);

		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);

		bigint &operator++();
		bigint operator++(int);

		bigint operator<<(unsigned int n) const;
		bigint operator<<(const bigint &n) const;
		bigint &operator<<=(unsigned int n);
		bigint &operator<<=(const bigint &n);
		bigint operator>>(unsigned int n) const;
		bigint operator>>(const bigint &n) const;
		bigint &operator>>=(unsigned int n);
		bigint &operator>>=(const bigint &n);

		bool operator<(const bigint &other) const;
		bool operator<=(const bigint &other) const;
		bool operator>(const bigint &other) const;
		bool operator>=(const bigint &other) const;

		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;
};


#endif
