#include "Color.hpp"

using namespace Tin;

//Construction and Destruction
Color::Color() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
}

Color::Color(const uint8_t& r, const uint8_t& g, const uint8_t& b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

Color::Color(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}