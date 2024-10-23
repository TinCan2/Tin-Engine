#pragma once
#include "ModuleDefinitions.hpp"
#include <cstdint>

namespace Tin {
	struct Vector2D;

	class Circle;
	class Rectangle;

	typedef const uint16_t cuint16_t;

	class JointShape {
		public:
		JointShape(Circle* cSubs, cuint16_t& cCount, Rectangle* rSubs, cuint16_t& rCount, const Vector2D& center);

		JointShape(const JointShape& copiedObject);
		JointShape& operator=(const JointShape& copiedObject);

		~JointShape();

		void SetCenter(const Vector2D& center);
		Vector2D GetCenter() const;

		void SetOrientation(const float& orientation);
		float GetOrientation() const;

		uint16_t GetCircleCount() const;
		Circle GetCircle(cuint16_t& index) const;
		uint16_t GetRectangleCount() const;
		Rectangle GetRectangle(cuint16_t& index) const;

		Circle GetEnclosure() const;

		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			bool CollidesWith(const Circle& otherShape, Vector2D* contact, Vector2D* normal) const;
			bool CollidesWith(const Rectangle& otherShape, Vector2D* contact, Vector2D* normal) const;
			bool CollidesWith(const JointShape& otherShape, Vector2D* contact, Vector2D* normal) const;
		#endif

		private:
		static Circle CircleFrom2(const Circle& circleA, const Circle& circleB);
		static Circle CircleFrom3(const Circle& circleA, const Circle& circleB, const Circle& circleC);
		static Circle Welzl(Circle** P, cuint16_t& pCount, Circle** R, cuint16_t& rCount);

		Circle** circleSubs;
		Rectangle** rectangleSubs;

		uint16_t circleCount, rectangleCount;

		Vector2D* center;
		float orientation;

		Circle* enclosure;
	};
}