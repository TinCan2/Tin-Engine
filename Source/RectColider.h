#pragma once

namespace Tin {
	struct Vector2D;

	class CircleColider;
	class LineColider;

	class RectColider {
		public:
		RectColider(const Vector2D& center, const Vector2D& extents, float orientation=0);
		RectColider(const RectColider& copiedColider);
		~RectColider();

		Vector2D GetCenter() const;
		Vector2D GetExtents() const;
		float GetOrientation() const;

		bool ColidesWith(const CircleColider& otherColider);
		bool ColidesWith(const LineColider& otherColider);
		bool ColidesWith(const RectColider& otherColider);

		private:
		Vector2D* center;
		Vector2D* extents;
		float orientation;
	};
}