#include "CircleColider.h"
#include "Vector2D.h"

//Construction and destruction
CircleColider::CircleColider(const Vector2D& origin, float radius) {
	this->origin = new Vector2D(origin);
	this->radius = radius;
}

CircleColider::~CircleColider() {
	delete this->origin;
}