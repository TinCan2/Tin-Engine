#include "LineColider.h"
#include "Vector2D.h"

using namespace Tin;

//Construction and Destruction
LineColider::LineColider(const Vector2D& base, const Vector2D& tip) {
	this->base = new Vector2D(base);
	this->tip = new Vector2D(tip);
}

LineColider::~LineColider() {
	delete this->base;
	delete this->tip;
}


//Component Access
Vector2D LineColider::GetBase() const {
	return *this->base;
}

Vector2D LineColider::GetTip() const {
	return *this->tip;
}