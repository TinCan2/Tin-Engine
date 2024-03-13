#pragma once
#include "Vector2D.h"

struct CircleColider {
	CircleColider(const Vector2D& origin, float radius);
	~CircleColider();

	Vector2D origin;
	float radius;
};