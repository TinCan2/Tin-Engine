#include "Circle.h"
#include "Vector2D.h"
#include <cmath>

using namespace Tin;

//Construction and Destruction
Circle::Circle(const Vector2D& center, float radius) {
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

void Circle::SetRadius(float radius) {
	this->radius = fabs(radius);
}