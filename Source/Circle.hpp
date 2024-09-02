#pragma once
#include "DllMacro.hpp"

namespace Tin {
	struct Vector2D;

	#ifdef TIN_MODULES_INCLUDE_PHYSICS
		class CollisionInfo;
		class Rectangle;
		class JointShape;
	#endif

	class TIN_API Circle {
		public:
		Circle(const Vector2D& center, const float& radius);

		Circle(const Circle& copiedCircle);
		Circle& operator=(const Circle& copiedCircle);

		~Circle();

		Vector2D GetCenter() const;
		float GetRadius() const;

		void SetCenter(const Vector2D& center);
		void SetRadius(const float& radius);

		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			bool CollidesWith(const Circle& otherShape, CollisionInfo* const& collisionInfo) const;
			bool CollidesWith(const Rectangle& otherShape, CollisionInfo* const& collisionInfo) const;
			bool CollidesWith(const JointShape& otherShape, CollisionInfo* const& collisionInfo) const;
		#endif

		private:
		Vector2D* center;
		float radius;
	};
}