#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {

}

vect2::vect2(int x, int y) : x(x), y(y) {

}

vect2::vect2(const vect2 &copy) : x(copy.x), y(copy.y) {
}

vect2 &vect2::operator=(const vect2 &copy) {
	if (this != &copy) {
		x = copy.x;
		y = copy.y;
	}
	return *this;
}

vect2::~vect2() {

}

// same as declaration, remove "friend"
std::ostream &operator<<(std::ostream &os, const vect2 &v) {
	os << "{" << v.x << ", " << v.y << "}";
	return os;
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

vect2 &vect2::operator+=(const vect2 &v) {
	x = x + v.x;
	y = y + v.y;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &v) {
	x = x - v.x;
	y = y - v.y;
	return *this;
}

vect2 vect2::operator-() const {
	vect2 tmp;
	tmp.x = -x;
	tmp.y = -y;
	return tmp;
}

vect2 vect2::operator+(const vect2 &other) const {
	vect2 tmp;
	tmp.x = this->x + other.x;
	tmp.y = this->y + other.y;
	return tmp;
}

vect2 vect2::operator-(const vect2 &other) const {
	vect2 tmp;
	tmp.x = this->x - other.x;
	tmp.y = this->y - other.y;
	return tmp;
}

vect2 vect2::operator*(int scalar) const {
	vect2 tmp;
	tmp.x = this->x * scalar;
	tmp.y = this->y * scalar;
	return tmp;
}
