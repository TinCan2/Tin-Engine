#pragma once
<<<<<<< HEAD
#include <cstdint>

namespace Tin {

	struct Color {
		uint8_t r, g, b, a;

		Color();
		Color(uint8_t r, uint8_t g, uint8_t b);
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
=======
#include "DllMacro.hpp"

namespace Tin {
	typedef unsigned char UInt8;

	struct TIN_API Color {
		UInt8 r, g, b, a;

		Color();
		Color(const UInt8& r, const UInt8& g, const UInt8& b);
		Color(const UInt8& r, const UInt8& g, const UInt8& b, const UInt8& a);
>>>>>>> 876bff7246f2612e8d213ae58499696cb6b9fc0d
	};
}