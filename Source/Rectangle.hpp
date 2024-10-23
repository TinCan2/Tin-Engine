#pragma once
#include "ModuleDefinitions.hpp"

namespace Tin {
	struct Vector2D;

	class Circle;
	class JointShape;

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

		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			bool CollidesWith(const Circle& otherShape, Vector2D* contact, Vector2D* normal) const;
			bool CollidesWith(const Rectangle& otherShape, Vector2D* contact, Vector2D* normal) const;
			bool CollidesWith(const JointShape& otherShape, Vector2D* contact, Vector2D* normal) const;
		#endif

		private:
		Vector2D* center;
		Vector2D* extents;
		float orientation;

		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			static void LiangBarsky(Vector2D* p1, Vector2D* p2, const Vector2D& extents);
			bool AABBCollidesWith(const Rectangle& otherShape, Vector2D* contact, Vector2D* normal) const;
		#endif
	};
}