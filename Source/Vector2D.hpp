#pragma once
#include "DllMacro.hpp"
#include <cstdint>

namespace Tin {

	struct TIN_API Vector2D {
		float x, y;

		Vector2D();
		Vector2D(const float& x, const float& y);

		float GetMagnitude();
		float GetMagnitude2();

		Vector2D FlipH();
		Vector2D FlipV();

		constexpr static uint16_t UnitPixelEquivalent = 16;
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