#pragma once

namespace Tin {
	struct Vector2D;
	class CircleColider {
		public:
		CircleColider(const Vector2D& center, const float r);
		~CircleColider();

		Vector2D GetCenter() const;
		float GetRadius() const ;

		private:
		Vector2D* center;
		float r;
	};
}