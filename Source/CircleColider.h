#pragma once

namespace Tin {
	struct Vector2D;

	class LineColider;
	class RectColider;

	class CircleColider {
		public:
		CircleColider(const Vector2D& center, const float r);
		~CircleColider();

		Vector2D GetCenter() const;
		float GetRadius() const ;

		bool ColidesWith(const CircleColider& otherColider);
		bool ColidesWith(const LineColider& otherColider);
		bool ColidesWith(const RectColider& otherColider);

		private:
		Vector2D* center;
		float r;
	};
}