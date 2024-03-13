#include "LineColider.h"
#include "Vector2D.h"

//Line Types
enum class LineColider::LineType {
	Line,
	Ray,
	Segment
};


//Construciton and Destruction
LineColider::LineColider(const Vector2D& base, const Vector2D& direction) {
	this->base = new Vector2D(base);
	this->tip = new Vector2D();
	this->type = LineType::Segment;
}

LineColider::LineColider(const Vector2D& base, const Vector2D& direction, LineType type) {
	this->base = new Vector2D(base);
	this->tip = new Vector2D();
	this->type = type;
}

LineColider::~LineColider() {
	delete this->base;
	delete this->tip;
}