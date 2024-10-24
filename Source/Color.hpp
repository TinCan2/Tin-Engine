#pragma once
#include "DllMacro.hpp"
#include <cstdint>

namespace Tin {

	struct TIN_API Color {
		uint8_t r, g, b, a;

		Color();

		Color(const uint8_t& r, const uint8_t& g, const uint8_t& b);
		Color(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a);
	};
}