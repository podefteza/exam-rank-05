#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
  private:
	int x;
	int y;

  public:
	vect2();								// default constructor (0, 0)
	vect2(int x, int y);					// parameterized constructor
	vect2(const vect2 &copy);				// copy constructor
	vect2 &operator=(const vect2 &other);	// copy assignment operator
	~vect2();								// destructor

	// used to access x and y by index: [0] = x, [1] = y
	// non-const version for assignment, const version for read-only access
	int &operator[](int i);
	const int &operator[](int i) const;

	// arithmetic operators, declared as const since they do not modify the current object
	vect2 operator-() const;
	//vect2 operator+() const; // not needed
	vect2 operator+(const vect2 &other) const;
	vect2 operator-(const vect2 &other) const;
	vect2 operator*(int scalar) const;

	// compound assignment operators, declared as non-const since they modify the current object
	vect2 &operator+=(const vect2 &other);
	vect2 &operator-=(const vect2 &other);
	vect2 &operator*=(int scalar);

	// pre-increment operators
	// & to return a reference to the modified object
	vect2 &operator++();
	vect2 &operator--();
	// post-increment operators
	// int parameter to distinguish from pre-increment, returns a copy of the original object before modification
	vect2 operator++(int);
	vect2 operator--(int);

	// const, since they do not modify the current object, just compare with another vect2
	bool operator==(const vect2 &other) const;
	bool operator!=(const vect2 &other) const;

	// operator overload
	friend std::ostream &operator<<(std::ostream &os, const vect2 &v);
};

// used to allow scalar multiplication with scalar on the left: scalar * vect2
vect2 operator*(int scalar, const vect2 &v);

#endif
