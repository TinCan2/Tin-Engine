#pragma once

namespace Tin {
	struct Vector2D;

	class CollisionInfo;
	class Circle;
	class Rectangle;

	typedef unsigned int UInt16;

	class JointShape {
		public:
		JointShape(Circle* cSubs, const UInt16& cCount, Rectangle* rSubs, const UInt16& rCount, const Vector2D& center);

		JointShape(const JointShape& copiedObject);
		JointShape& operator=(const JointShape& copiedObject);

		~JointShape();

		void SetCenter(const Vector2D& center);
		Vector2D GetCenter() const;

		void SetOrientation(const float& orientation);
		float GetOrientation() const;

		UInt16 GetCircleCount() const;
		Circle GetCircle(const UInt16& index) const;
		UInt16 GetRectangleCount() const;
		Rectangle GetRectangle(const UInt16& index) const;

		Circle GetEnclosure() const;

		bool CollidesWith(const Circle& otherShape, CollisionInfo* const& collisionInfo) const;
		bool CollidesWith(const Rectangle& otherShape, CollisionInfo* const& collisionInfo) const;
		bool CollidesWith(const JointShape& otherShape, CollisionInfo* const& collisionInfo) const;

		private:
		static Circle CircleFrom2(const Circle& circleA, const Circle& circleB);
		static Circle CircleFrom3(const Circle& circleA, const Circle& circleB, const Circle& circleC);
		static Circle Welzl(Circle** P, const UInt16& pCount, Circle** R, const UInt16& rCount);

		Circle** circleSubs;
		Rectangle** rectangleSubs;

		UInt16 circleCount, rectangleCount;

		Vector2D* center;
		float orientation;

		Circle* enclosure;
	};
}