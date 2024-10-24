#include "Circle.hpp"
#include "Vector2D.hpp"
#include <cmath>

#ifdef TIN_MODULES_INCLUDE_PHYSICS
	#include "Rectangle.hpp"
	#include "JointShape.hpp"
#endif

using namespace Tin;

//Construction and Destruction
Circle::Circle(const Vector2D& center, const float& radius) {
	this->center = new Vector2D(center);
	this->radius = std::abs(radius);
}

Circle::Circle(const Circle& copiedCircle) {
	this->center = new Vector2D(*copiedCircle.center);
	this->radius = copiedCircle.radius;
}

Circle& Circle::operator=(const Circle& copiedCircle) {
	*this->center = *copiedCircle.center;
	this->radius = copiedCircle.radius;

	return *this;
}

Circle::~Circle() {
	delete this->center;
}


//Component Access
Vector2D Circle::GetCenter() const {
	return *this->center;
}

float Circle::GetRadius() const {
	return this->radius;
}

void Circle::SetCenter(const Vector2D& center) {
	*this->center = center;
}

void Circle::SetRadius(const float& radius) {
	this->radius = std::abs(radius);
}


//Collision Detection
#ifdef TIN_MODULES_INCLUDE_PHYSICS
	bool Circle::CollidesWith(const Circle& otherShape, Vector2D* contact, Vector2D* normal) const{
		Vector2D dir = otherShape.GetCenter() - this->GetCenter();
		float rS = this->GetRadius();
		float rO = otherShape.GetRadius();

		float rT = rS+rO;
		bool overlapping = dir.GetMagnitude2() < rT*rT;

		if (overlapping) {
			float d = dir.GetMagnitude();
			float depth = (rS+rO)-d;

			if(normal != nullptr) *normal = depth*dir/(d+0.1/Vector2D::UnitPixelEquivalent);
			if (contact != nullptr) {
				if (d <= std::abs(rS-rO)) *contact = (rS < rO) ? this->GetCenter() : otherShape.GetCenter();
				else {
					float l = (rS*rS - rO*rO)/(2*d*d) + 0.5;
					*contact = this->GetCenter() + l*dir;
				}
			}
		}
		return overlapping;
	}

	bool Circle::CollidesWith(const Rectangle& otherShape, Vector2D* contact, Vector2D* normal) const {
		bool overlapping = otherShape.CollidesWith(*this, contact, normal);
		if (overlapping && normal != nullptr) *normal *= -1;
		return overlapping;
	}

	bool Circle::CollidesWith(const JointShape& otherShape, Vector2D* contact, Vector2D* normal) const {
		bool overlapping = otherShape.CollidesWith(*this, contact, normal);
		if (overlapping && normal != nullptr) *normal *= -1;
		return overlapping;
	}
#endif