#include "Circle.h"
#include "Vector2D.h"

using namespace Tin;

//Construction and Destruction
Circle::Circle(const Vector2D& center, float radius) {
	if (radius <= 0) throw "Invalid radius.";
	this->center = new Vector2D(center);
	this->radius = radius;
}

Circle::Circle(const Circle& coppied) {
	this->center = new Vector2D(*coppied.center);
	this->radius = coppied.radius;
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