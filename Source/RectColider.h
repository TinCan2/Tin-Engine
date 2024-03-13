#pragma once
#include "Vector2D.h"

struct Vector2D;

class RectColider {
	RectColider(const Vector2D& center, const Vector2D& extents);
	~RectColider();

	Vector2D center;
	Vector2D extents;

	float orientation;
};