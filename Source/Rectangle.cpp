#include "Rectangle.hpp"
#include "Vector2D.hpp"
#include <cmath>

using namespace Tin;

//Construction and Destruction
Rectangle::Rectangle(const Vector2D& center, const Vector2D& extents, const float& orientation) {
	this->center = new Vector2D(center);
	this->extents = new Vector2D(fabs(extents.x), fabs(extents.y));
	this->orientation = orientation;
}

Rectangle::Rectangle(const Rectangle& copiedRectangle) {
	this->center = new Vector2D(*copiedRectangle.center);
	this->extents = new Vector2D(*copiedRectangle.extents);
	this->orientation = copiedRectangle.orientation;
}

Rectangle& Rectangle::operator=(const Rectangle& copiedRectangle) {
	*this->center = *copiedRectangle.center;
	*this->extents = *copiedRectangle.extents;
	this->orientation = copiedRectangle.orientation;

	return *this;
}

Rectangle::~Rectangle() {
	delete this->center;
	delete this->extents;
}


//Component Access
Vector2D Rectangle::GetCenter() const {
	return *this->center;
}

Vector2D Rectangle::GetExtents() const {
	return *this->extents;
}

float Rectangle::GetOrientation() const {
	return this->orientation;
}

void Rectangle::SetCenter(const Vector2D& center) {
	*this->center = center;
}

void Rectangle::SetExtents(const Vector2D& extents) {
	this->extents->x = fabs(extents.x);
	this->extents->y = fabs(extents.y);
}

void Rectangle::SetOrientation(const float& orientation) {
	this->orientation = orientation;
}