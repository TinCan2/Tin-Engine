#pragma once

namespace Tin {
	struct Vector2D;

	class Circle {
		public:
		Circle(const Vector2D& center, const float& radius);

		Circle(const Circle& copiedCircle);
		Circle& operator=(const Circle& copiedCircle);

		~Circle();

		Vector2D GetCenter() const;
		float GetRadius() const;

		void SetCenter(const Vector2D& center);
		void SetRadius(const float& radius);

		private:
		Vector2D* center;
		float radius;
	};
}