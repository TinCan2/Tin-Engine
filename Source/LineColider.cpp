#include "LineColider.h"
#include "Vector2D.h"

//Line Types
enum class LineColider::LineType {
	Line,
	Ray,
	Segment
};


//Construciton and Destruction
LineColider::LineColider(const Vector2D& base, const Vector2D& tip) {
	this->base = base;
	this->tip = tip;
	this->type = LineType::Segment;
}

LineColider::LineColider(const Vector2D& base, const Vector2D& tip, LineType type) {
	this->base = base;
	this->tip = tip;
	this->type = type;
}

LineColider::~LineColider() {}