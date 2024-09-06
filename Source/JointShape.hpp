#pragma once
#include "DllMacro.hpp"
#include <cstdint>

namespace Tin {
	struct Vector2D;

	#ifdef TIN_MODULES_INCLUDE_PHYSICS
		class CollisionInfo;
	#endif

	class Circle;
	class Rectangle;

	class TIN_API JointShape {
		public:
		JointShape(Circle* cSubs, const uint16_t& cCount, Rectangle* rSubs, const uint16_t& rCount, const Vector2D& center);

		JointShape(const JointShape& copiedObject);
		JointShape& operator=(const JointShape& copiedObject);

		~JointShape();

		void SetCenter(const Vector2D& center);
		Vector2D GetCenter() const;

		void SetOrientation(const float& orientation);
		float GetOrientation() const;

		uint16_t GetCircleCount() const;
		Circle GetCircle(const uint16_t& index) const;
		uint16_t GetRectangleCount() const;
		Rectangle GetRectangle(const uint16_t& index) const;

		Circle GetEnclosure() const;

		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			bool CollidesWith(const Circle& otherShape, CollisionInfo* const& collisionInfo) const;
			bool CollidesWith(const Rectangle& otherShape, CollisionInfo* const& collisionInfo) const;
			bool CollidesWith(const JointShape& otherShape, CollisionInfo* const& collisionInfo) const;
		#endif

		private:
		static Circle CircleFrom2(const Circle& circleA, const Circle& circleB);
		static Circle CircleFrom3(const Circle& circleA, const Circle& circleB, const Circle& circleC);
		static Circle Welzl(Circle** P, const uint16_t& pCount, Circle** R, const uint16_t& rCount);

		Circle** circleSubs;
		Rectangle** rectangleSubs;

		uint16_t circleCount, rectangleCount;

		Vector2D* center;
		float orientation;

		Circle* enclosure;
	};
}