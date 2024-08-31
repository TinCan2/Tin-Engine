#include "Color.hpp"

using namespace Tin;

//Construction and Destruction
Color::Color() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
}

Color::Color(const UInt8& r, const UInt8& g, const UInt8& b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

Color::Color(const UInt8& r, const UInt8& g, const UInt8& b, const UInt8& a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}