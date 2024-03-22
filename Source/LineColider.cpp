#include "Camera.h"
#include "Color.h"
#include "DebugPainter.h"
#include "LineColider.h"
#include "Vector2D.h"
#include <cmath>
#include <utility>
#include <iostream>

//Construction and Destruction
LineColider::LineColider(const Vector2D& base, const Vector2D& tip) {
	if (base == tip) throw "The base and tip cannoct coincide for a line collider.";
	this->base = new Vector2D(base);
	this->tip = new Vector2D(tip);
	this->type = LineType::Segment;
}

LineColider::LineColider(const Vector2D& base, const Vector2D& tip, LineType type) {
	if (base == tip) throw "The base and tip cannoct coincide for a line collider.";
	this->base = new Vector2D(base);
	this->tip = new Vector2D(tip);
	this->type = type;
}

LineColider::~LineColider() {
	delete this->base;
	delete this->tip;
}


//Component Access
Vector2D LineColider::GetBase() {
	return *this->base;
}

Vector2D LineColider::GetTip() {
	return *this->tip;
}

LineColider::LineType LineColider::GetType() {
	return this->type;
}


//Colision Check
bool LineColider::Coliding(const LineColider& coliderA, const LineColider& coliderB) {
	Vector2D dirA = *coliderA.tip-*coliderA.base;
	Vector2D dirB = *coliderB.tip-*coliderB.base;

	float mA = (dirA.x == 0) ? HUGE_VALF :dirA.y/dirA.x;
	float mB = (dirB.x == 0) ? HUGE_VALF :dirB.y/dirB.x;

	Vector2D interBasePath = *coliderB.base - *coliderA.base;

	if (mA == mB || fabs(mA - mB)*Vector2D::UnitPixelEquivalent < 0.5) {
//		std::cout << "Parallel Lines" << std::endl;

		if (fabs((interBasePath.y/interBasePath.x) - mA)*Vector2D::UnitPixelEquivalent >= 0.5) return false;

		std::pair<float, float> tIntA;
		tIntA.first = (coliderA.type == LineType::Line) ? -HUGE_VALF : 0;
		tIntA.second = (coliderA.type == LineType::Segment) ? 1 : HUGE_VALF;

		std::pair<float, float> tIntB;
		if (dirA.x != 0) {
			tIntB.first = (coliderB.type == LineType::Line) ? -HUGE_VALF*dirB.x : (*coliderB.base-*coliderA.base).x / dirA.x;
			tIntB.second = (coliderB.type == LineType::Segment) ? (*coliderB.tip-*coliderA.base).x / dirA.x : HUGE_VALF*dirB.x;
		}
		else{
			tIntB.first = (coliderB.type == LineType::Line) ? -HUGE_VALF*dirB.y : (*coliderB.base-*coliderA.base).y / dirA.y;
			tIntB.second = (coliderB.type == LineType::Segment) ? (*coliderB.tip-*coliderA.base).y / dirA.y : HUGE_VALF*dirB.y;
		}
		if (tIntB.first > tIntB.second) std::swap(tIntB.first, tIntB.second);

		return !(tIntA.second < tIntB.first || tIntA.first > tIntB.second);
	}
	else {
//		std::cout << "Intersecting Lines" << std::endl;

		std::pair<float, float> tIntA;
		tIntA.first = (coliderA.type == LineType::Line) ? -HUGE_VALF : 0;
		tIntA.second = (coliderA.type == LineType::Segment) ? 1 : HUGE_VALF;

		std::pair<float, float> tIntB;
		tIntB.first = (coliderB.type == LineType::Line) ? -HUGE_VALF : 0;
		tIntB.second = (coliderB.type == LineType::Segment) ? 1 : HUGE_VALF;

		float systemMatrix[2][3] = {{dirA.x, -dirB.x, interBasePath.x}, {dirA.y, -dirB.y, interBasePath.y}};

//		std::cout << "Printing the system matrix." << std::endl;
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < 3; j++) std::cout << systemMatrix[i][j] << " ";
//			std::cout << std::endl;
//		}


		float tA, tB;
		if (systemMatrix[0][0] != 0) {
			float leadingCoefficient = systemMatrix[1][0];
			for (int i = 0; i < 3; i++) systemMatrix[1][i] -= systemMatrix[0][i]*leadingCoefficient/systemMatrix[0][0];

			 tB = systemMatrix[1][2]/systemMatrix[1][1];
			 tA = (systemMatrix[0][2]-tB*systemMatrix[0][1])/systemMatrix[0][0];
		}
		else {
			float leadingCoefficient = systemMatrix[0][0];
			for (int i = 0; i < 3; i++) systemMatrix[0][i] -= systemMatrix[1][i]*leadingCoefficient/systemMatrix[1][0];

			 tB = systemMatrix[0][2]/systemMatrix[0][1];
			 tA = (systemMatrix[1][2]-tB*systemMatrix[1][1])/systemMatrix[1][0];
		}

//		std::cout << "Printing the stair-form matrix." << std::endl;
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < 3; j++) std::cout << systemMatrix[i][j] << " ";
//			std::cout << std::endl;
//		}
//
//		std::cout << "tA:" << tA << std::endl;
//		std::cout << "tB:" << tB << std::endl;

		return (tIntA.first <= tA && tA <= tIntA.second) && (tIntB.first <= tB && tB <= tIntB.second);
	}
}

//Visualization
void LineColider::Visualize() {
	Vector2D camPos = Camera::GetCurrentInstance()->GetPosition();
	Vector2D camExt = Camera::GetCurrentInstance()->GetExtents();

	float t0 = (this->type == LineType::Line) ? -HUGE_VALF : 0;
	float t1 = (this->type == LineType::Segment) ? 1 : HUGE_VALF;

	Vector2D dir = *this->tip - *this->base;

	float p, q, r;
	for (int i = 0; i < 4; i++) {
		switch (i) {
			case 0:
				p = -dir.x;
				q = this->base->x - (camPos.x - camExt.x);
			break;
			case 1:
				p = dir.x;
				q = (camPos.x + camExt.x) - this->base->x;
			break;
			case 2:
				p = -dir.y;
				q = this->base->y - (camPos.y - camExt.y);
			break;
			case 3:
				p = dir.y;
				q = (camPos.y + camExt.y) - this->base->y;
			break;
		}

		if (p < 0) {
			r = q/p;
			if (r > t1) return;
			else if (r > t0) t0 = r;
		}
		else if (p > 0) {
			r = q/p;
			if (r < t0) return;
			else if (r < t1) t1 = r;
		}
		else if (q < 0 ) return;
	}

	DebugPainter::PaintLine(*this->base + t0*dir, *this->base + t1*dir);

}