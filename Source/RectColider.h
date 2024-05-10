#pragma once

namespace Tin {
	struct Vector2D;

	class RectColider {
		public:
		RectColider(const Vector2D& center, const Vector2D& extents, float orientation=0);
		~RectColider();

		Vector2D GetCenter() const;
		Vector2D GetExtents() const;
		float GetOrientation() const;

		private:
		Vector2D* center;
		Vector2D* extents;
		float orientation;
	};
}