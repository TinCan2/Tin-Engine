#pragma once

namespace Tin {
	typedef unsigned int UInt16;

	struct Vector2D {
		float x, y;

		Vector2D();
		Vector2D(float x, float y);

		float GetMagnitude();
		float GetMagnitude2();

		Vector2D FlipH();
		Vector2D FlipV();

		friend Vector2D operator+(const Vector2D& a, const Vector2D& b);

		friend Vector2D operator+=(Vector2D& a, const Vector2D& b);

		friend Vector2D operator-(const Vector2D& a);
		friend Vector2D operator-(const Vector2D& a, const Vector2D& b);

		friend Vector2D operator-=(Vector2D& a, const Vector2D& b);

		friend Vector2D operator*(const Vector2D& a, const float& b);
		friend Vector2D operator*(const float& a, const Vector2D& b);
		friend float operator*(const Vector2D& a, const Vector2D& b);

		friend float operator^(const Vector2D& a, const Vector2D& b);

		friend Vector2D operator*=(Vector2D& a, const float& b);

		friend Vector2D operator/(const Vector2D& a, const float& b);

		friend Vector2D operator/=(Vector2D& a, const float& b);

		friend bool operator==(const Vector2D& a, const Vector2D& b);

		constexpr static UInt16 UnitPixelEquivalent = 16;
	};
}