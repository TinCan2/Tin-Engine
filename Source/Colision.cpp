#include "CircleColider.h"
#include "LineColider.h"
#include "RectColider.h"
#include "Vector2D.h"
#include <algorithm>
#include <cmath>

using namespace Tin;

//Homogeneous Colisions
bool CircleCircle(const CircleColider& coliderA, const CircleColider& coliderB) {
	Vector2D interCenterPath = coliderB.GetCenter() - coliderA.GetCenter();
	float d = coliderA.GetRadius() + coliderB.GetRadius();

	return interCenterPath.GetMagnitude2() <= d*d;
}

bool LineLine(const LineColider& coliderA, const LineColider& coliderB) {
	Vector2D dirA = coliderA.GetTip() - coliderA.GetBase();
	Vector2D dirB = coliderB.GetTip() - coliderB.GetBase();

	Vector2D aTbB = coliderB.GetBase() - coliderA.GetTip();
	Vector2D aTbT = coliderB.GetTip() - coliderA.GetTip();
	float cpAdBb = dirA.x*aTbB.y - dirA.y*aTbB.x;
	float cpAdBt = dirA.x*aTbT.y - dirA.y*aTbT.x;
	if (cpAdBb*cpAdBt > 0) return false;

	Vector2D bTaB = coliderA.GetBase() - coliderB.GetTip();
	Vector2D bTaT = -aTbT;
	float cpBdAb = dirB.x*bTaB.y - dirB.y*bTaB.x;
	float cpBdAt = dirB.x*bTaT.y - dirB.y*bTaT.x;

	if (cpBdAb*cpBdAt > 0) return false;

	return true;
}

bool RectRect(const RectColider& coliderA, const RectColider& coliderB) {
	Vector2D icp = coliderB.GetCenter() - coliderA.GetCenter();

	std::pair<float, float> xPr;
	std::pair<float, float> yPr;

	Vector2D tIcp = icp.x*Vector2D(cos(coliderA.GetOrientation()), sin(-coliderA.GetOrientation()));
	tIcp += icp.y*Vector2D(sin(coliderA.GetOrientation()), cos(coliderA.GetOrientation()));
	float theta = coliderB.GetOrientation() - coliderA.GetOrientation();

	Vector2D tExt = coliderB.GetExtents().x*Vector2D(cos(theta), sin(theta)) + coliderB.GetExtents().y*Vector2D(-sin(theta), cos(theta));
	Vector2D tExtF = -coliderB.GetExtents().x*Vector2D(cos(theta), sin(theta)) + coliderB.GetExtents().y*Vector2D(-sin(theta), cos(theta));

	xPr.first = std::min({tIcp.x+tExt.x, tIcp.x-tExt.x, tIcp.x+tExtF.x, tIcp.x-tExtF.x});
	xPr.second = std::max({tIcp.x+tExt.x, tIcp.x-tExt.x, tIcp.x+tExtF.x, tIcp.x-tExtF.x});
	yPr.first = std::min({tIcp.y+tExt.y, tIcp.y-tExt.y, tIcp.y+tExtF.y, tIcp.y-tExtF.y});
	yPr.second = std::max({tIcp.y+tExt.y, tIcp.y-tExt.y, tIcp.y+tExtF.y, tIcp.y-tExtF.y});

	if (xPr.first > coliderA.GetExtents().x || xPr.second < -coliderA.GetExtents().x) return false;
	if (yPr.first > coliderA.GetExtents().y || yPr.second < -coliderA.GetExtents().y) return false;

	tIcp = -icp.x*Vector2D(cos(coliderB.GetOrientation()), sin(-coliderB.GetOrientation()));
	tIcp -= icp.y*Vector2D(sin(coliderB.GetOrientation()), cos(coliderB.GetOrientation()));
	theta *= -1;

	tExt = coliderA.GetExtents().x*Vector2D(cos(theta), sin(theta)) + coliderA.GetExtents().y*Vector2D(-sin(theta), cos(theta));
	tExtF = -coliderA.GetExtents().x*Vector2D(cos(theta), sin(theta)) + coliderA.GetExtents().y*Vector2D(-sin(theta), cos(theta));

	xPr.first = std::min({tIcp.x+tExt.x, tIcp.x-tExt.x, tIcp.x+tExtF.x, tIcp.x-tExtF.x});
	xPr.second = std::max({tIcp.x+tExt.x, tIcp.x-tExt.x, tIcp.x+tExtF.x, tIcp.x-tExtF.x});
	yPr.first = std::min({tIcp.y+tExt.y, tIcp.y-tExt.y, tIcp.y+tExtF.y, tIcp.y-tExtF.y});
	yPr.second = std::max({tIcp.y+tExt.y, tIcp.y-tExt.y, tIcp.y+tExtF.y, tIcp.y-tExtF.y});

	if (xPr.first > coliderB.GetExtents().x || xPr.second < -coliderB.GetExtents().x) return false;
	if (yPr.first > coliderB.GetExtents().y || yPr.second < -coliderB.GetExtents().y) return false;

	return true;
}


//Heterogenous Colisions
bool CircleLine(const CircleColider& coliderA, const LineColider& coliderB) {
	Vector2D base2Cent = coliderA.GetCenter() - coliderB.GetBase();
	Vector2D dir = coliderB.GetTip() - coliderB.GetBase();

	float dot = base2Cent*dir;

	float l2 = base2Cent.GetMagnitude2() - std::clamp(dot*dot/dir.GetMagnitude2(), 0.0f, dir.GetMagnitude2());
	float r = coliderA.GetRadius();
	return l2 <= r*r;
}

bool LineRect(const LineColider& coliderA, const RectColider& coliderB) {
	Vector2D ext = coliderB.GetExtents();

	Vector2D c2b = coliderA.GetBase() - coliderB.GetCenter();
	Vector2D c2t = coliderA.GetTip() - coliderB.GetCenter();

	float theta = coliderB.GetOrientation();
	Vector2D tc2b = c2b.x*Vector2D(cos(theta), sin(-theta)) + c2b.y*Vector2D(sin(theta), cos(theta));
	Vector2D tc2t = c2t.x*Vector2D(cos(theta), sin(-theta)) + c2t.y*Vector2D(sin(theta), cos(theta));

	std::pair<float, float> xPr;
	xPr.first = (tc2b.x < tc2t.x) ? tc2b.x : tc2t.x;
	xPr.second = (tc2b.x > tc2t.x) ? tc2b.x : tc2t.x;

	std::pair<float, float> yPr;
	yPr.first = (tc2b.y < tc2t.y) ? tc2b.y : tc2t.y;
	yPr.second = (tc2b.y > tc2t.y) ? tc2b.y : tc2t.y;

	if (xPr.first > ext.x || xPr.second < -ext.x) return false;
	if (yPr.first > ext.y || yPr.second < -ext.y) return false;

	Vector2D tExt = ext.x*Vector2D(cos(theta), sin(theta)) + ext.y*Vector2D(-sin(theta), cos(theta));
	Vector2D tExtF = -ext.x*Vector2D(cos(theta), sin(theta)) + ext.y*Vector2D(-sin(theta), cos(theta));

	Vector2D corners[] = {tExt-c2b, -tExt-c2b, tExtF-c2b, -tExtF-c2b};
	Vector2D dir = c2t-c2b;
	float cross = dir.x*corners[0].y-dir.y*corners[0].x;
	for (int i = 1; i < 4; i++) {
		if (cross*(dir.x*corners[i].y-dir.y*corners[i].x) < 0) return true;
	}

	return false;
}

bool RectCircle(const RectColider& coliderA, const CircleColider& coliderB) {
	Vector2D icp = coliderB.GetCenter() - coliderA.GetCenter();
	Vector2D tIcp = icp.x*Vector2D(cos(coliderA.GetOrientation()), sin(-coliderA.GetOrientation()));
	tIcp += icp.y*Vector2D(sin(coliderA.GetOrientation()), cos(coliderA.GetOrientation()));

	float clampX = std::clamp(tIcp.x, coliderA.GetExtents().x, -coliderA.GetExtents().x);
	float clampY = std::clamp(tIcp.y, coliderA.GetExtents().y, -coliderA.GetExtents().y);
	Vector2D clampPoint(clampX,clampY);

	float r = coliderB.GetRadius();
	return clampPoint.GetMagnitude2() <= r*r;
}


//Colider Implementations
bool CircleColider::ColidesWith(const CircleColider& otherColider) {return CircleCircle(*this, otherColider);}
bool CircleColider::ColidesWith(const LineColider& otherColider) {return CircleLine(*this, otherColider);}
bool CircleColider::ColidesWith(const RectColider& otherColider) {return RectCircle(otherColider, *this);}

bool LineColider::ColidesWith(const CircleColider& otherColider) {return CircleLine(otherColider, *this);}
bool LineColider::ColidesWith(const LineColider& otherColider) {return LineLine(*this, otherColider);}
bool LineColider::ColidesWith(const RectColider& otherColider) {return LineRect(*this, otherColider);}

bool RectColider::ColidesWith(const CircleColider& otherColider) {return RectCircle(*this, otherColider);}
bool RectColider::ColidesWith(const LineColider& otherColider) {return LineRect(otherColider, *this);}
bool RectColider::ColidesWith(const RectColider& otherColider) {return RectRect(*this, otherColider);}