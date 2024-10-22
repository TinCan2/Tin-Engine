#include "Color.h"

using namespace Tin;

//Construction and Destruction
Color::Color() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
}

Color::Color(UInt8 r, UInt8 g, UInt8 b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

Color::Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}