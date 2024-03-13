#pragma once

struct Vector2D;

class CircleColider {
	public:
	CircleColider(const Vector2D& origin, float radius);
	~CircleColider();

	private:
	Vector2D* origin;
	float radius;
};