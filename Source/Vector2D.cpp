#include "Vector2D.h"
#include <cmath>

using namespace Tin;

//Construction and Destruction
Vector2D::Vector2D() {
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}


//Magnitude
float Vector2D::GetMagnitude() {
	return pow(this->x * this->x + this->y * this->y, 0.5);
}

float Vector2D::GetMagnitude2() {
	return this->x * this->x + this->y * this->y;
}


//Flipping
Vector2D Vector2D::FlipH() {
	return Vector2D(-this->x, this->y);
}

Vector2D Vector2D::FlipV() {
	return Vector2D(this->x, -this->y);
}


//Operators
Vector2D Tin::operator+(const Vector2D& a, const Vector2D& b) {
	return Vector2D(a.x + b.x, a.y + b.y);
}

Vector2D Tin::operator+=(Vector2D& a, const Vector2D& b) {
	a.x += b.x;
	a.y += b.y;
	return Vector2D(a);
}

Vector2D Tin::operator-(const Vector2D& a) {
	return Vector2D(-a.x, -a.y);
}

Vector2D Tin::operator-(const Vector2D& a, const Vector2D& b) {
	return Vector2D(a.x - b.x, a.y - b.y);
}

Vector2D Tin::operator-=(Vector2D& a, const Vector2D& b) {
	a.x -= b.x;
	a.y -= b.y;
	return Vector2D(a);
}

Vector2D Tin::operator*(const Vector2D& a, const float& b) {
	return Vector2D(a.x * b, a.y * b);
}

Vector2D Tin::operator*(const float& a, const Vector2D& b) {
	return Vector2D(a * b.x, a * b.y);
}

float Tin::operator*(const Vector2D& a, const Vector2D& b) {
	return a.x*b.x + a.y*b.y;
}

Vector2D Tin::operator*=(Vector2D& a, const float& b) {
	a.x *= b;
	a.y *= b;
	return Vector2D(a);
}

Vector2D Tin::operator/(const Vector2D& a, const float& b) {
	return Vector2D(a.x / b, a.y / b);
}

Vector2D Tin::operator/=(Vector2D& a, const float& b) {
	a.x /= b;
	a.y /= b;
	return Vector2D(a);
}

bool Tin::operator==(const Vector2D& a, const Vector2D& b) {
	return (std::abs(a.x - b.x)*Vector2D::UnitPixelEquivalent < 0.5f) && (std::abs(a.y - b.y)*Vector2D::UnitPixelEquivalent < 0.5f);
}