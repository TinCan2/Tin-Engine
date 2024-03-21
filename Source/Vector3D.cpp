#include "Vector2D.h"
#include "Vector3D.h"
#include <cmath>

//Construction and Destruction
Vector3D::Vector3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3D::Vector3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(const Vector3D& coppiedVector) {
	this->x = coppiedVector.x;
	this->y = coppiedVector.y;
	this->z = coppiedVector.z;
}


//Magnitude
float Vector3D::GetMagnitude() {
	return pow(this->x*this->x + this->y*this->y + this->z*this->z , 0.5);
}

float Vector3D::GetMagnitude2() {
	return this->x*this->x + this->y*this->y + this->z*this->z;
}


//Operators
Vector3D operator+(const Vector3D& a, const Vector3D& b) {
	return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3D operator+=(Vector3D& a, const Vector3D& b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return Vector3D(a);
}

Vector3D operator-(const Vector3D& a) {
	return Vector3D(-a.x, -a.y, -a.z);
}

Vector3D operator-(const Vector3D& a, const Vector3D& b) {
	return Vector3D(a.x - b.x, a.y - b.y, a.z-b.z);
}

Vector3D operator-=(Vector3D& a, const Vector3D& b) {
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return Vector3D(a);
}

Vector3D operator*(const Vector3D& a, const float& b) {
	return Vector3D(a.x * b, a.y * b, a.z * b);
}

Vector3D operator*(const float& a, const Vector3D& b) {
	return Vector3D(a * b.x, a * b.y, a * b.z);
}

float operator*(const Vector3D& a, const Vector3D& b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3D operator*=(Vector3D& a, const float& b) {
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return Vector3D(a);
}

Vector3D operator/(const Vector3D& a, const float& b) {
	return Vector3D(a.x / b, a.y / b, a.z / b);
}

Vector3D operator/=(Vector3D& a, const float& b) {
	a.x /= b;
	a.y /= b;
	a.z /= b;
	return Vector3D(a);
}

bool operator==(const Vector3D& a, const Vector3D& b) {
	bool output = std::abs(a.x - b.x)*Vector2D::UnitPixelEquivalent < 0.5f;
	output &= std::abs(a.y - b.y)*Vector2D::UnitPixelEquivalent < 0.5f;
	output &= std::abs(a.z - b.z)*Vector2D::UnitPixelEquivalent < 0.5f;
	return output;
}

Vector3D operator^(const Vector3D& a, const Vector3D& b) {
	return Vector3D(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y);
}

Vector3D::operator Vector2D() {
	return Vector2D(this->x, this->y);
}