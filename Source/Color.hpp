#pragma once

namespace Tin {
	typedef unsigned char UInt8;

	struct Color {
		UInt8 r, g, b, a;

		Color();
		Color(UInt8 r, UInt8 g, UInt8 b);
		Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a);
	};
}