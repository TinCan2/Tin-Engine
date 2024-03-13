#include "RectColider.h"
#include "Vector2D.h"

//Construction and Destruction

RectColider::RectColider(const Vector2D& center, const Vector2D& extents) {
	this->center = center;
	this->extents = extents;
}

RectColider::~RectColider() {}