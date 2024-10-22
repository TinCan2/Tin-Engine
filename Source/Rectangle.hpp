#pragma once

namespace Tin {
	struct Vector2D;

	class Rectangle {
		public:
		Rectangle(const Vector2D& center, const Vector2D& extents, const float& orientation=0);

		Rectangle(const Rectangle& copiedRectangle);
		Rectangle& operator=(const Rectangle& copiedRectangle);

		~Rectangle();

		Vector2D GetCenter() const;
		Vector2D GetExtents() const;
		float GetOrientation() const;

		void SetCenter(const Vector2D& center);
		void SetExtents(const Vector2D& extents);
		void SetOrientation(const float& orientation);

		private:
		Vector2D* center;
		Vector2D* extents;
		float orientation;
	};
}