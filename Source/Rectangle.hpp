#pragma once
#include "DllMacro.hpp"

namespace Tin {
	struct Vector2D;

	#ifdef TIN_MODULES_INCLUDE_PHYSICS
		class CollisionInfo;
		class Circle;
		class JointShape;
	#endif

	class TIN_API Rectangle {
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
			bool CollidesWith(const Circle& otherShape, CollisionInfo* const& collisionInfo) const;
			bool CollidesWith(const Rectangle& otherShape, CollisionInfo* const& collisionInfo) const;
			bool CollidesWith(const JointShape& otherShape, CollisionInfo* const& collisionInfo) const;
		#endif

		private:
		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			static void LiangBarsky(Vector2D* p1, Vector2D* p2, const Vector2D& extents);
		#endif

		Vector2D* center;
		Vector2D* extents;
		float orientation;
	};
}