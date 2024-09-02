#pragma once
#include "DllMacro.hpp"

namespace Tin {
	typedef unsigned char UInt8;

	struct TIN_API Color {
		UInt8 r, g, b, a;

		Color();
		Color(const UInt8& r, const UInt8& g, const UInt8& b);
		Color(const UInt8& r, const UInt8& g, const UInt8& b, const UInt8& a);
	};
}