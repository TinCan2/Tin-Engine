#pragma once
#include "Vector2D.h"

struct LineColider {
	enum class LineType;

	LineColider(const Vector2D& base, const Vector2D& tip);
	LineColider(const Vector2D& base, const Vector2D& tip, LineType type);
	~LineColider();

	Vector2D base;
	Vector2D tip;

	LineType type;
};