#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
	private:
		int x;
		int y;

	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2 &copy);				//copy constructor
		vect2 &operator=(const vect2 &copy);	//copy assignement
		~vect2();

		int &operator[](int i);
		const int &operator[](int i) const;

		vect2 &operator++();
		vect2 &operator--();
		vect2 operator++(int);
		vect2 operator--(int);

		vect2 &operator+=(const vect2 &v);
		vect2 &operator-=(const vect2 &v);

		//vect2 operator+() const;
		vect2 operator-() const;
		vect2 operator+(const vect2 &other) const;
		vect2 operator-(const vect2 &other) const;
		vect2 operator*(int scalar) const;






	// ostream
	friend std::ostream &operator<<(std::ostream &os, const vect2 &v);
};

// multiply


#endif
