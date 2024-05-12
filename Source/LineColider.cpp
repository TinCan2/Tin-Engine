#include "LineColider.h"
#include "Vector2D.h"
#include <stdexcept>

using namespace Tin;

//Construction and Destruction
LineColider::LineColider(const Vector2D& base, const Vector2D& tip) {
	if (base == tip) throw std::runtime_error("Invalid line colider.");
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