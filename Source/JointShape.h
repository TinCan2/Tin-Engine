#pragma once

namespace Tin {
	struct Vector2D;

	class Circle;
	class Rectangle;

	typedef unsigned int UInt16;

	class JointShape {
		public:
		JointShape(Circle* cSubs, UInt16 cCount, Rectangle* rSubs, UInt16 rCount, const Vector2D& center);

		JointShape(const JointShape& copiedObject);
		JointShape& operator=(const JointShape& copiedObject);

		~JointShape();

		void SetCenter(const Vector2D& center);
		Vector2D GetCenter() const;

		void SetOrientation(const float& orientation);
		float GetOrientation() const;

		UInt16 GetCircleCount() const;
		Circle GetCircle(UInt16 index) const;
		UInt16 GetRectangleCount() const;
		Rectangle GetRectangle(UInt16 index) const;

		Circle GetEnclosure() const;

		private:
		Circle** circleSubs;
		Rectangle** rectangleSubs;

		UInt16 circleCount, rectangleCount;

		Vector2D* center;
		float orientation;

		Circle* enclosure;
	};
}