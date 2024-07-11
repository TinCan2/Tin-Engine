#pragma once

namespace Tin {
	struct Vector2D;

	class Circle {
		public:
		Circle(const Vector2D& center, float radius);
		Circle(const CircleColider& coppiedColider);

		~Circle();

		Vector2D GetCenter() const;
		float GetRadius() const;

		private:
		Vector2D* center;
		float radius;
	};
}