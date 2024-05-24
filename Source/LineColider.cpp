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

LineColider::LineColider(const LineColider& copiedColider) {
	this->base = new Vector2D(*copiedColider.base);
	this->tip = new Vector2D(*copiedColider.tip);
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

void LineColider::SetBase(const Vector2D& base) {
	if (base == *this->tip) throw std::runtime_error("Invalid line colider.");
	*this->base = base;
}

void LineColider::SetTip(const Vector2D& tip) {
	if (*this->base == tip) throw std::runtime_error("Invalid line colider.");
	*this->tip = tip;
}