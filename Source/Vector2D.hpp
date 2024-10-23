#pragma once
#include "DllMacro.hpp"

namespace Tin {
	typedef unsigned int UInt16;

	struct TIN_API Vector2D {
		float x, y;

		Vector2D();
		Vector2D(const float& x, const float& y);

		float GetMagnitude() const;
		float GetMagnitude2() const;

		Vector2D FlipH();
		Vector2D FlipV();

		constexpr static UInt16 UnitPixelEquivalent = 16;
	};

	TIN_API Vector2D operator+(const Vector2D& a, const Vector2D& b);

	TIN_API Vector2D operator+=(Vector2D& a, const Vector2D& b);

	TIN_API Vector2D operator-(const Vector2D& a);
	TIN_API Vector2D operator-(const Vector2D& a, const Vector2D& b);

	TIN_API Vector2D operator-=(Vector2D& a, const Vector2D& b);

	TIN_API Vector2D operator*(const Vector2D& a, const float& b);
	TIN_API Vector2D operator*(const float& a, const Vector2D& b);
	TIN_API float operator*(const Vector2D& a, const Vector2D& b);

	TIN_API float operator^(const Vector2D& a, const Vector2D& b);

	TIN_API Vector2D operator*=(Vector2D& a, const float& b);

	TIN_API Vector2D operator/(const Vector2D& a, const float& b);

	TIN_API Vector2D operator/=(Vector2D& a, const float& b);

	TIN_API bool operator==(const Vector2D& a, const Vector2D& b);
}