#pragma once

struct Vector2D;

class LineColider {
	public:
	enum class LineType;

	LineColider(const Vector2D& base, const Vector2D& direction);
	LineColider(const Vector2D& base, const Vector2D& direction, LineType type);
	~LineColider();

	private:
	Vector2D* base;
	Vector2D* tip;

	LineType type;
};