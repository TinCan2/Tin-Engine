#pragma once
#include "ModuleDefinitions.hpp"

namespace Tin {
	struct Vector2D;

	class Rectangle;
	class JointShape;

	class Circle {
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
			bool CollidesWith(const Circle& otherShape, Vector2D* contact, Vector2D* normal) const;
			bool CollidesWith(const Rectangle& otherShape, Vector2D* contact, Vector2D* normal) const;
			bool CollidesWith(const JointShape& otherShape, Vector2D* contact, Vector2D* normal) const;
		#ifdef TIN_MODULES_INCLUDE_PHYSICS

		private:
		Vector2D* center;
		float radius;
	};
}