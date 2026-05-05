// TODO: create or comment comparing the changes from hpp to cpp

#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {
}

vect2::vect2(int x, int y) : x(x), y(y) {
}

vect2::vect2(const vect2 &copy) : x(copy.x), y(copy.y) {
}

vect2::~vect2() {
}

vect2 &vect2::operator=(const vect2 &other) {
	if (this != &other) {
		x = other.x;
		y = other.y;
	}
	return *this;
}

int &vect2::operator[](int i) {
	if (i == 0)
		return x;
	return y;
}

const int &vect2::operator[](int i) const {
	if (i == 0)
		return x;
	return y;
}

vect2 vect2::operator-() const {
	return vect2(-x, -y);
}

vect2 vect2::operator+(const vect2 &other) const {
	return vect2(x + other.x, y + other.y);
}

vect2 vect2::operator-(const vect2 &other) const {
	return vect2(x - other.x, y - other.y);
}

vect2 vect2::operator*(int scalar) const {
	return vect2(x * scalar, y * scalar);
}

vect2 &vect2::operator+=(const vect2 &other) {
	x += other.x;
	y += other.y;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

vect2 &vect2::operator*=(int scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

vect2 &vect2::operator++() {
	x++;
	y++;
	return *this;
}

vect2 &vect2::operator--() {
	x--;
	y--;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 tmp = *this;
	x++;
	y++;
	return tmp;
}

vect2 vect2::operator--(int) {
	vect2 tmp = *this;
	x--;
	y--;
	return tmp;
}

bool vect2::operator==(const vect2 &other) const {
	return (x == other.x && y == other.y);
}

bool vect2::operator!=(const vect2 &other) const {
	return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const vect2 &v) {
	os << "{" << v.x << ", " << v.y << "}";
	return os;
}

vect2 operator*(int scalar, const vect2 &v) {
	return v * scalar; // calls the member operator*
}
