#include <iostream>

#ifndef WIP_VECT2_HPP
#define WIP_VECT2_HPP

class vect2 {
	private:
		int x;
		int y;

	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2 &copy);
		vect2 &operator=(const vect2 &other);
		~vect2();

		int &operator[](int i);
		const int &operator[](int i) const;

		vect2 operator-() const;
		vect2 operator+(const vect2 &other) const;
		vect2 operator-(const vect2 &other) const;
		vect2 operator*(int scalar) const;

		vect2 &operator+=(const vect2 &other);
		vect2 &operator-=(const vect2 &other);
		vect2 &operator*=(int scalar);

		vect2 &operator++();
		vect2 &operator--();
		vect2 operator++(int);
		vect2 operator--(int);

		bool operator==(const vect2 &other) const;
		bool operator!=(const vect2 &other) const;


	// operator overload to print value of the vector
	friend std::ostream &operator<<(std::ostream &os, const vect2 &v);
};

vect2 operator*(int scalar, const vect2 &v);

#endif
