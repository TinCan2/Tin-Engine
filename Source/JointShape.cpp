#include "Circle.hpp"
#include "JointShape.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"
#include <cmath>

using namespace Tin;

//Enclosure Functions
Circle JointShape::CircleFrom2(const Circle& circleA, const Circle& circleB) {
	Vector2D dir = circleB.GetCenter() - circleA.GetCenter();
	float r = (circleA.GetRadius() + circleB.GetRadius() + dir.GetMagnitude())/2;

	float d = dir.GetMagnitude();
	float t = (d != 0) ? (r - circleA.GetRadius())/d : 0;
	Vector2D center = circleA.GetCenter() + t*dir;
	return Circle(center, r);
}

Circle JointShape::CircleFrom3(const Circle& circleA, const Circle& circleB, const Circle& circleC) {
    Vector2D centerA = circleA.GetCenter();
    Vector2D centerB = circleB.GetCenter();
    Vector2D centerC = circleC.GetCenter();
    float r1 = circleA.GetRadius();
    float r2 = circleB.GetRadius();
    float r3 = circleC.GetRadius();

    float x1 = centerA.x, y1 = centerA.y;
    float x2 = centerB.x, y2 = centerB.y;
    float x3 = centerC.x, y3 = centerC.y;

    float a2 = x1 - x2, b2 = y1 - y2, c2 = r2 - r1;
    float a3 = x1 - x3, b3 = y1 - y3, c3 = r3 - r1;

    float d1 = x1 * x1 + y1 * y1 - r1 * r1;
    float d2 = d1 - (x2 * x2 + y2 * y2 - r2 * r2);
    float d3 = d1 - (x3 * x3 + y3 * y3 - r3 * r3);

    float ab = a3 * b2 - a2 * b3;
    float xa = (b2 * d3 - b3 * d2) / (2 * ab) - x1;
    float xb = (b3 * c2 - b2 * c3) / ab;
    float ya = (a3 * d2 - a2 * d3) / (2 * ab) - y1;
    float yb = (a2 * c3 - a3 * c2) / ab;

    float A = xb * xb + yb * yb - 1;
    float B = 2 * (r1 + xa * xb + ya * yb);
    float C = xa * xa + ya * ya - r1 * r1;

    float r = -(A != 0 ? (B + std::sqrt(B * B - 4 * A * C)) / (2 * A) : C / B);
    Vector2D center = {x1 + xa + xb * r, y1 + ya + yb * r};

    return Circle(center, r);
}

Circle JointShape::Welzl(Circle** P, cuint16_t& pCount, Circle** R, cuint16_t& rCount) {
    if (pCount == 0 || rCount == 3) {
        switch (rCount) {
        	case 1:
        		return *R[0];
        		break;
            case 2:
                return CircleFrom2(*R[0], *R[1]);
                break;
            case 3:
                return CircleFrom3(*R[0], *R[1], *R[2]);
                break;
            default:
                return Circle(Vector2D(0, 0), 0);
                break;
        }
    }

    Circle* p = P[pCount - 1];
    Circle D = Welzl(P, pCount - 1, R, rCount);

    float r = std::max(D.GetRadius() - p->GetRadius(), 0.0f);
    if ((D.GetCenter() - p->GetCenter()).GetMagnitude2() < r * r) return D;

    Circle** Rnew = new Circle*[rCount + 1];
    for (UInt16 i = 0; i < rCount; i++) Rnew[i] = R[i];
    Rnew[rCount] = p;
    Circle result = Welzl(P, pCount - 1, Rnew, rCount + 1);
    delete[] Rnew;
    return result;
}


//Construction and Destruction
JointShape::JointShape(Circle* cSubs, cuint16_t& cCount, Rectangle* rSubs, cuint16_t& rCount, const Vector2D& center) {
	this->circleCount = cCount;
	if (cCount != 0) {
		this->circleSubs = new Circle*[cCount];
		for (UInt16 i = 0; i < cCount; i++) this->circleSubs[i] = new Circle(cSubs[i]);
	}

	this->rectangleCount = rCount;
	if (rCount != 0) {
		this->rectangleSubs = new Rectangle*[rCount];
		for (UInt16 i = 0; i < rCount; i++) this->rectangleSubs[i] = new Rectangle(rSubs[i]);
	}

	this->center = new Vector2D(center);
	this->orientation = 0;

	Circle** subEnclosures = new Circle*[rCount + cCount];
	for (int i = 0; i < cCount; i++) subEnclosures[i] = &cSubs[i];
	for (int i = 0; i < rCount; i++) subEnclosures[cCount+i] = new Circle(rSubs[i].GetCenter(), rSubs[i].GetExtents().GetMagnitude());
	Circle a(Welzl(subEnclosures, rCount + cCount, nullptr, 0));
	this-> enclosure = new Circle(a);
	for (int i = 0; i < rCount; i++) delete subEnclosures[cCount+i];
	delete[] subEnclosures;
}

JointShape::JointShape(const JointShape& copiedObject) {
	this->circleCount = copiedObject.circleCount;
	if (this->circleCount != 0) {
		this->circleSubs = new Circle*[this->circleCount];
		for (UInt16 i = 0; i < this->circleCount; i++) this->circleSubs[i] = new Circle(*copiedObject.circleSubs[i]);
	}

	this->rectangleCount = copiedObject.rectangleCount;
	if (this->rectangleCount != 0) {
		this->rectangleSubs = new Rectangle*[this->rectangleCount];
		for (UInt16 i = 0; i < this->rectangleCount; i++) this->rectangleSubs[i] = new Rectangle(*copiedObject.rectangleSubs[i]);
	}

	this->center = new Vector2D(*copiedObject.center);
	this->orientation = copiedObject.orientation;

	this->enclosure = new Circle(*copiedObject.enclosure);
}

JointShape& JointShape::operator=(const JointShape& copiedObject) {
	if (this->circleCount != 0) {
		for (UInt16 i = 0; i < this->circleCount; i++) delete this->circleSubs[i];
		delete[] this-> circleSubs;
	}

	if (this->rectangleCount != 0) {
		for (UInt16 i = 0; i < this->rectangleCount; i++) delete this->rectangleSubs[i];
		delete[] this-> rectangleSubs;
	}

	this->circleCount = copiedObject.circleCount;
	if (this->circleCount != 0) {
		this->circleSubs = new Circle*[this->circleCount];
		for (UInt16 i = 0; i < this->circleCount; i++) this->circleSubs[i] = new Circle(*copiedObject.circleSubs[i]);
	}

	this->rectangleCount = copiedObject.rectangleCount;
	if (this->rectangleCount != 0) {
		this->rectangleSubs = new Rectangle*[this->rectangleCount];
		for (UInt16 i = 0; i < this->rectangleCount; i++) this->rectangleSubs[i] = new Rectangle(*copiedObject.rectangleSubs[i]);
	}

	*this->center = *copiedObject.center;
	this->orientation = copiedObject.orientation;

	*this->enclosure = *copiedObject.enclosure;

	return *this;
}

JointShape::~JointShape() {
	if (this->circleCount != 0) {
		for (UInt16 i = 0; i < this->circleCount; i++) delete this->circleSubs[i];
		delete[] this-> circleSubs;
	}

	if (this->rectangleCount != 0) {
		for (UInt16 i = 0; i < this->rectangleCount; i++) delete this->rectangleSubs[i];
		delete[] this-> rectangleSubs;
	}

	delete this->enclosure;
}


//Component Access
void JointShape::SetCenter(const Vector2D& center) {
	Vector2D displacement = center-*this->center;

	for (UInt16 i = 0; i < this->circleCount; i++) this->circleSubs[i]->SetCenter(this->circleSubs[i]->GetCenter() + displacement);
	for (UInt16 i = 0; i < this->rectangleCount; i++) this->rectangleSubs[i]->SetCenter(this->rectangleSubs[i]->GetCenter() + displacement);
	this->enclosure->SetCenter(this->enclosure->GetCenter() + displacement);

	*this->center = center;
}

Vector2D JointShape::GetCenter() const {
	return *this->center;
}

void JointShape::SetOrientation(const float& orientation) {
	float theta = orientation - this->orientation;

	for (UInt16 i = 0; i < this->circleCount; i++) {
		Vector2D localCenter = this->circleSubs[i]->GetCenter() - this->GetCenter();
		Vector2D tLoc = localCenter.x*Vector2D(cos(theta),sin(theta)) + localCenter.y*Vector2D(-sin(theta),cos(theta));
		this->circleSubs[i]->SetCenter(this->GetCenter()+tLoc);
	}

	for (UInt16 i = 0; i < this->rectangleCount; i++) {
		Vector2D localCenter = this->rectangleSubs[i]->GetCenter() - this->GetCenter();
		Vector2D tLoc = localCenter.x*Vector2D(cos(theta),sin(theta)) + localCenter.y*Vector2D(-sin(theta),cos(theta));
		this->rectangleSubs[i]->SetCenter(this->GetCenter()+tLoc);
		this->rectangleSubs[i]->SetOrientation(this->rectangleSubs[i]->GetOrientation() + theta);
	}

	Vector2D dir = this->enclosure->GetCenter() - *this->center;
	Vector2D tDir = dir.x*Vector2D(cos(theta), sin(theta)) + dir.y*Vector2D(-sin(theta), cos(theta));
	this->enclosure->SetCenter(*this->center + tDir);

	this->orientation = orientation;
}

float JointShape::GetOrientation() const {
	return this->orientation;
}


//Colider Access
uint16_t JointShape::GetCircleCount() const {
	return this->circleCount;
}

Circle JointShape::GetCircle(cuint16_t& index) const {
	return *this->circleSubs[index];
}

uint16_t JointShape::GetRectangleCount() const {
	return this->rectangleCount;
}

Rectangle JointShape::GetRectangle(cuint16_t& index) const {
	return *this->rectangleSubs[index];
}


//Enclosure Access
Circle JointShape::GetEnclosure() const {
	return *this->enclosure;
}


//Collision Detection
#ifdef TIN_MODULES_INCLUDE_PHYSICS
	bool JointShape::CollidesWith(const Circle& otherShape, Vector2D* contact, Vector2D* normal) const {
		if (!this->enclosure->CollidesWith(otherShape, nullptr, nullptr)) return false;

		if (contact == nullptr && normal == nullptr) {
			for (size_t i = 0; i < this->circleCount; i++) {
				if (this->circleSubs[i]->CollidesWith(otherShape, nullptr, nullptr)) return true;
			}
			for (size_t i = 0; i < this->rectangleCount; i++) {
				if (this->rectangleSubs[i]->CollidesWith(otherShape, nullptr, nullptr)) return true;
			}
			return false;
		}
		else {
			Vector2D deepestContact, deepestNormal;
			bool overlapping = false;
			for (size_t i = 0; i < this->circleCount; i++) {
				Vector2D currentContact, currentNormal;
				if (this->circleSubs[i]->CollidesWith(otherShape, &currentContact, &currentNormal)) {
					if (currentNormal.GetMagnitude2() > deepestNormal.GetMagnitude2()) {
						deepestContact = currentContact;
						deepestNormal = currentNormal;
					}
					overlapping = true;
				}
			}

			for (size_t i = 0; i < this->rectangleCount; i++) {
				Vector2D currentContact, currentNormal;
				if (this->rectangleSubs[i]->CollidesWith(otherShape, &currentContact, &currentNormal)) {
					if (currentNormal.GetMagnitude2() > deepestNormal.GetMagnitude2()) {
						deepestContact = currentContact;
						deepestNormal = currentNormal;
					}
					overlapping = true;
				}
			}

			if (overlapping) {
				*contact = deepestContact;
				*normal = deepestNormal;
			}
			return overlapping;
		}
	}

	bool JointShape::CollidesWith(const Rectangle& otherShape, Vector2D* contact, Vector2D* normal) const {
		Circle rectEnclosure(otherShape.GetCenter(), otherShape.GetExtents().GetMagnitude());
		if (!this->enclosure->CollidesWith(rectEnclosure, nullptr, nullptr)) return false;

		if (contact == nullptr && normal == nullptr) {
			for (size_t i = 0; i < this->circleCount; i++) {
				if (this->circleSubs[i]->CollidesWith(otherShape, nullptr, nullptr)) return true;
			}
			for (size_t i = 0; i < this->rectangleCount; i++) {
				if (this->rectangleSubs[i]->CollidesWith(otherShape, nullptr, nullptr)) return true;
			}
			return false;
		}
		else {
			Vector2D deepestContact, deepestNormal;
			bool overlapping = false;
			for (size_t i = 0; i < this->circleCount; i++) {
				Vector2D currentContact, currentNormal;
				if (this->circleSubs[i]->CollidesWith(otherShape, &currentContact, &currentNormal)) {
					if (currentNormal.GetMagnitude2() > deepestNormal.GetMagnitude2()) {
						deepestContact = currentContact;
						deepestNormal = currentNormal;
					}
					overlapping = true;
				}
			}

			for (size_t i = 0; i < this->rectangleCount; i++) {
				Vector2D currentContact, currentNormal;
				if (this->rectangleSubs[i]->CollidesWith(otherShape, &currentContact, &currentNormal)) {
					if (currentNormal.GetMagnitude2() > deepestNormal.GetMagnitude2()) {
						deepestContact = currentContact;
						deepestNormal = currentNormal;
					}
					overlapping = true;
				}
			}

			if (overlapping) {
				*contact = deepestContact;
				*normal = deepestNormal;
			}
			return overlapping;
		}
	}

	bool JointShape::CollidesWith(const JointShape& otherShape, Vector2D* contact, Vector2D* normal) const {
		if (!this->enclosure->CollidesWith(otherShape.GetEnclosure(), nullptr, nullptr)) return false;

		if (contact == nullptr && normal == nullptr) {
			for (size_t i = 0; i < this->circleCount; i++) {
				if (this->circleSubs[i]->CollidesWith(otherShape, nullptr, nullptr)) return true;
			}
			for (size_t i = 0; i < this->rectangleCount; i++) {
				if (this->rectangleSubs[i]->CollidesWith(otherShape, nullptr, nullptr)) return true;
			}
			return false;
		}
		else {
			Vector2D deepestContact, deepestNormal;
			bool overlapping = false;
			for (size_t i = 0; i < this->circleCount; i++) {
				Vector2D currentContact, currentNormal;
				if (this->circleSubs[i]->CollidesWith(otherShape, &currentContact, &currentNormal)) {
					if (currentNormal.GetMagnitude2() > deepestNormal.GetMagnitude2()) {
						deepestContact = currentContact;
						deepestNormal = currentNormal;
					}
					overlapping = true;
				}
			}

			for (size_t i = 0; i < this->rectangleCount; i++) {
				Vector2D currentContact, currentNormal;
				if (this->rectangleSubs[i]->CollidesWith(otherShape, &currentContact, &currentNormal)) {
					if (currentNormal.GetMagnitude2() > deepestNormal.GetMagnitude2()) {
						deepestContact = currentContact;
						deepestNormal = currentNormal;
					}
					overlapping = true;
				}
			}

			if (overlapping) {
				*contact = deepestContact;
				*normal = deepestNormal;
			}
			return overlapping;
		}
	}
#endif