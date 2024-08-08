#include "Circle.h"
#include "CollisionInfo.h"
#include "JointShape.h"
#include "Rectangle.h"
#include "Vector2D.h"
#include <cmath>
#include <algorithm>

using namespace Tin;

//Construction and Destruction
Rectangle::Rectangle(const Vector2D& center, const Vector2D& extents, const float& orientation) {
	this->center = new Vector2D(center);
	this->extents = new Vector2D(fabs(extents.x), fabs(extents.y));
	this->orientation = orientation;
}

Rectangle::Rectangle(const Rectangle& copiedRectangle) {
	this->center = new Vector2D(*copiedRectangle.center);
	this->extents = new Vector2D(*copiedRectangle.extents);
	this->orientation = copiedRectangle.orientation;
}

Rectangle& Rectangle::operator=(const Rectangle& copiedRectangle) {
	*this->center = *copiedRectangle.center;
	*this->extents = *copiedRectangle.extents;
	this->orientation = copiedRectangle.orientation;

	return *this;
}

Rectangle::~Rectangle() {
	delete this->center;
	delete this->extents;
}


//Component Access
Vector2D Rectangle::GetCenter() const {
	return *this->center;
}

Vector2D Rectangle::GetExtents() const {
	return *this->extents;
}

float Rectangle::GetOrientation() const {
	return this->orientation;
}

void Rectangle::SetCenter(const Vector2D& center) {
	*this->center = center;
}

void Rectangle::SetExtents(const Vector2D& extents) {
	this->extents->x = fabs(extents.x);
	this->extents->y = fabs(extents.y);
}

void Rectangle::SetOrientation(const float& orientation) {
	this->orientation = orientation;
}


//Collision Helpers
void Rectangle::LiangBarsky(Vector2D* p1, Vector2D* p2, const Vector2D& extents) {
	Vector2D dir = *p2 - *p1;
	float p[] = {-dir.x, dir.x, -dir.y, dir.y};
	float q[] = {p1->x+extents.x, extents.x-p1->x, p1->y+extents.y, extents.y-p1->y};

	float t1 = 0, t2 = 1;

	for (UInt16 i = 0; i < 4; i++) {
		if (p[i] == 0) continue;
		float t = q[i]/p[i];
		(p[i] < 0) ? t1 = std::max(t, t1) : t2 = std::min(t, t2);
	}

	*p2 = *p1 + t2*dir;
	*p1 = *p1 + t1*dir;
}


//Collision Detection
bool Rectangle::CollidesWith(const Circle& otherShape, CollisionInfo* const& collisionInfo) const {
	Circle enclosure(this->GetCenter(), this->GetExtents().GetMagnitude());
	if (!enclosure.CollidesWith(otherShape, nullptr)) return false;

	float r = otherShape.GetRadius();

	float theta = this->GetOrientation();
	Vector2D ext = this->GetExtents();

	Vector2D axH(cos(theta), sin(theta));
	Vector2D axV(-sin(theta), cos(theta));

	Vector2D dir = otherShape.GetCenter() - this->GetCenter();
	Vector2D tDir = dir.x*axH.FlipV() + dir.y*axV.FlipH();
	Vector2D clampPoint = Vector2D(std::clamp(tDir.x, -ext.x, ext.x), std::clamp(tDir.y, -ext.y, ext.y));

	bool overlapping = (tDir-clampPoint).GetMagnitude2() < r*r;

	if (overlapping && collisionInfo != nullptr) {
		if (fabs(tDir.x) <= ext.x && fabs(tDir.y) <= ext.y) {
			float depth =  std::min(ext.x-fabs(tDir.x), ext.y-fabs(tDir.y)) + r;
			float eps = 0.1/Vector2D::UnitPixelEquivalent;

			bool minPenAxX = ext.x-fabs(tDir.x) < ext.y-fabs(tDir.y);
			*collisionInfo->normal = (minPenAxX) ? axH*tDir.x/(fabs(tDir.x)+eps) : axV*tDir.y/(fabs(tDir.y)+eps);
			*collisionInfo->normal *= depth;
		}
		else {
			float depth = r - (tDir-clampPoint).GetMagnitude();
			*collisionInfo->normal = (tDir-clampPoint);
			*collisionInfo->normal = collisionInfo->normal->x*axH + collisionInfo->normal->y*axV;
			*collisionInfo->normal *= depth/collisionInfo->normal->GetMagnitude();
		}

		*collisionInfo->contact = clampPoint.x*axH + clampPoint.y*axV;
		*collisionInfo->contact += this->GetCenter();
	}

	return overlapping;
}

bool Rectangle::CollidesWith(const Rectangle& otherShape, CollisionInfo* const& collisionInfo) const {
	//Preliminary enclosure overlap check
	Circle enclosureS(this->GetCenter(), this->GetExtents().GetMagnitude());
	Circle enclosureO(otherShape.GetCenter(), otherShape.GetExtents().GetMagnitude());
	if (!enclosureS.CollidesWith(enclosureO, nullptr)) return false;

	//Determine the axes and vertices
	float thetaS = this->GetOrientation();
	float thetaO = otherShape.GetOrientation();

	Vector2D axSh(cos(thetaS), sin(thetaS));
	Vector2D axSv(-sin(thetaS), cos(thetaS));
	Vector2D axOh(cos(thetaO), sin(thetaO));
	Vector2D axOv(-sin(thetaO), cos(thetaO));

	Vector2D cS = this->GetCenter();
	Vector2D cO = otherShape.GetCenter();
	Vector2D extS = this->GetExtents();
	Vector2D extO = otherShape.GetExtents();

	Vector2D vertS[] = {cS+extS.x*axSh+extS.y*axSv, cS+extS.x*axSh-extS.y*axSv,
						cS-extS.x*axSh-extS.y*axSv, cS-extS.x*axSh+extS.y*axSv};
	Vector2D vertO[] = {cO+extO.x*axOh+extO.y*axOv, cO+extO.x*axOh-extO.y*axOv,
						cO-extO.x*axOh-extO.y*axOv, cO-extO.x*axOh+extO.y*axOv};

	//Sperating axis test
	std::pair<float, float> hProjection(std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest());
	std::pair<float, float> vProjection(std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest());

	Vector2D minNormal;
	float minDepth = std::numeric_limits<float>::max();
	bool referSelf = true;

	float eps = 0.1/Vector2D::UnitPixelEquivalent;

	for (UInt16 i = 0; i < 4; i ++) {
		float prH = (vertO[i]-cS)*axSh;
		if (prH < hProjection.first) hProjection.first = prH;
		if (prH > hProjection.second) hProjection.second = prH;

		float prV = (vertO[i]-cS)*axSv;
		if (prV < vProjection.first) vProjection.first = prV;
		if (prV > vProjection.second) vProjection.second = prV;
	}
	if (hProjection.first >= extS.x || hProjection.second <= -extS.x) return false;
	else if (collisionInfo != nullptr){
		float m = hProjection.first + hProjection.second;
		float depth = (m > 0) ? extS.x - hProjection.first : hProjection.second + extS.x;
		if (depth < minDepth) {
			minNormal = axSh * m/(fabs(m)+eps);
			minDepth = depth;
		}
	}
	if (vProjection.first >= extS.y || vProjection.second <= -extS.y) return false;
	else if (collisionInfo != nullptr){
		float m = vProjection.first + vProjection.second;
		float depth = (m > 0) ? extS.y - vProjection.first : vProjection.second + extS.y;
		if (depth < minDepth) {
			minNormal = axSv * m/(fabs(m)+eps);
			minDepth = depth;
		}
	}

	hProjection = std::pair<float, float>(std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest());
	vProjection = std::pair<float, float>(std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest());

	for (UInt16 i = 0; i < 4; i ++) {
		float prH = (vertS[i]-cO)*axOh;
		if (prH < hProjection.first) hProjection.first = prH;
		if (prH > hProjection.second) hProjection.second = prH;

		float prV = (vertS[i]-cO)*axOv;
		if (prV < vProjection.first) vProjection.first = prV;
		if (prV > vProjection.second) vProjection.second = prV;
	}
	if (hProjection.first >= extO.x || hProjection.second <= -extO.x) return false;
	else if (collisionInfo != nullptr){
		float m = hProjection.first + hProjection.second;
		float depth = (m > 0) ? extO.x - hProjection.first : hProjection.second + extO.x;
		if (depth < minDepth) {
			minNormal = axOh * m/(fabs(m)+eps);
			minDepth = depth;
			referSelf = false;
		}
	}
	if (vProjection.first >= extO.y || vProjection.second <= -extO.y) return false;
	else if (collisionInfo != nullptr){
		float m = vProjection.first + vProjection.second;
		float depth = (m > 0) ? extO.y - vProjection.first : vProjection.second + extO.y;
		if (depth < minDepth) {
			minNormal = axOv * m/(fabs(m)+eps);
			minDepth = depth;
			referSelf = false;
		}
	}

	//Normal and contact calculation
	if (collisionInfo != nullptr) {
		*collisionInfo->normal = referSelf ? minNormal*minDepth : -minNormal*minDepth;

		std::pair<Vector2D, Vector2D> incidentFace;
		std::pair<Vector2D, Vector2D> locInc;
		UInt16 deepestIndex = 0;
		if (referSelf) {
			for (UInt16 i = 1; i < 4; i++) if ((vertO[i]-cO)*minNormal < minNormal*(vertO[deepestIndex]-cO)) deepestIndex = i;
			incidentFace.first = vertO[deepestIndex];
			if (fabs(axOh*minNormal) < fabs(axOv*minNormal))incidentFace.second = vertO[3-deepestIndex];
			else incidentFace.second = vertO[(1-deepestIndex%2)+2*(deepestIndex/2)];

			locInc.first = incidentFace.first - cS;
			locInc.second = incidentFace.second - cS;
			locInc.first = locInc.first.x*axSh.FlipV() + locInc.first.y*axSv.FlipH();
			locInc.second = locInc.second.x*axSh.FlipV() + locInc.second.y*axSv.FlipH();

			LiangBarsky(&locInc.first, &locInc.second, extS);

			locInc.first = locInc.first.x*axSh + locInc.first.y*axSv;
			locInc.second = locInc.second.x*axSh + locInc.second.y*axSv;

			incidentFace.first = cS + locInc.first;
			incidentFace.second = cS + locInc.second;
		}
		else {
			for (UInt16 i = 1; i < 4; i++) if ((vertS[i]-cS)*minNormal < minNormal*(vertS[deepestIndex]-cS)) deepestIndex = i;
			incidentFace.first = vertS[deepestIndex];
			if (fabs(axSh*minNormal) < fabs(axSv*minNormal)) incidentFace.second = vertS[3-deepestIndex];
			else incidentFace.second = vertS[(1-deepestIndex%2)+2*(deepestIndex/2)];

			locInc.first = incidentFace.first - cO;
			locInc.second = incidentFace.second - cO;
			locInc.first = locInc.first.x*axOh.FlipV() + locInc.first.y*axOv.FlipH();
			locInc.second = locInc.second.x*axOh.FlipV() + locInc.second.y*axOv.FlipH();

			LiangBarsky(&locInc.first, &locInc.second, extO);

			locInc.first = locInc.first.x*axOh + locInc.first.y*axOv;
			locInc.second = locInc.second.x*axOh + locInc.second.y*axOv;

			incidentFace.first = cO + locInc.first;
			incidentFace.second = cO + locInc.second;
		}
		*collisionInfo->contact = (incidentFace.first + incidentFace.second)/2;
	}
	return true;
}

bool Rectangle::CollidesWith(const JointShape& otherShape, CollisionInfo* const& collisionInfo) const {
	bool overlapping = otherShape.CollidesWith(*this, collisionInfo);
	if (overlapping && collisionInfo != nullptr) *collisionInfo->normal *= -1;
	return overlapping;
}