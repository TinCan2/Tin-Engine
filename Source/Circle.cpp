#include "Circle.hpp"
#include "Vector2D.hpp"
#include <cmath>

using namespace Tin;

//Construction and Destruction
Circle::Circle(const Vector2D& center, const float& radius) {
	this->center = new Vector2D(center);
	this->radius = fabs(radius);
}

Circle::Circle(const Circle& copiedCircle) {
	this->center = new Vector2D(*copiedCircle.center);
	this->radius = copiedCircle.radius;
}

Circle& Circle::operator=(const Circle& copiedCircle) {
	*this->center = *copiedCircle.center;
	this->radius = copiedCircle.radius;

	return *this;
}

Circle::~Circle() {
	delete this->center;
}


//Component Access
Vector2D Circle::GetCenter() const {
	return *this->center;
}

float Circle::GetRadius() const {
	return this->radius;
}

void Circle::SetCenter(const Vector2D& center) {
	*this->center = center;
}

void Circle::SetRadius(const float& radius) {
	this->radius = fabs(radius);
}