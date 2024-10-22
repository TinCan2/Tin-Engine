#pragma once
#include <cstdint>

namespace Tin {

	struct Color {
		uint8_t r, g, b, a;

		Color();
		Color(uint8_t r, uint8_t g, uint8_t b);
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	};
}