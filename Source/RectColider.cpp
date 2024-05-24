#include "RectColider.h"
#include "Vector2D.h"
#include <cmath>

using namespace Tin;

//Construction and Destruction
RectColider::RectColider(const Vector2D& center, const Vector2D& extents, float orientation) {
	this->center = new Vector2D(center);
	this->extents = new Vector2D(fabs(extents.x), fabs(extents.y));
	this->orientation = orientation;
}

RectColider::RectColider(const RectColider& copiedColider) {
	this->center = new Vector2D(*copiedColider.center);
	this->extents = new Vector2D(*copiedColider.extents);
	this->orientation = orientation;
}

RectColider::~RectColider() {
	delete this->center;
	delete this->extents;
}


//Component Access
Vector2D RectColider::GetCenter() const {
	return *this->center;
}

Vector2D RectColider::GetExtents() const {
	return *this->extents;
}

float RectColider::GetOrientation() const {
	return this->orientation;
}

void RectColider::SetCenter(const Vector2D& center) {
	*this->center = center;
}

void RectColider::SetExtents(const Vector2D& extents) {
	this->extents->x = fabs(extents.x);
	this->extents->y = fabs(extents.y);
}

void RectColider::SetOrientation(const float& orientation) {
	this->orientation = orientation;
}