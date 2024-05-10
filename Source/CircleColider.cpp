#include "CircleColider.h"
#include "Vector2D.h"
#include <cmath>

using namespace Tin;

//Construction and Destruction
CircleColider::CircleColider(const Vector2D& center, const float r) {
	this->center = new Vector2D(center);
	this->r = fabs(r);
}

CircleColider::~CircleColider() {
	delete this->center;
}


//Component Access
Vector2D CircleColider::GetCenter() const {
	return *this->center;
}

float CircleColider::GetRadius() const {
	return this->r;
}