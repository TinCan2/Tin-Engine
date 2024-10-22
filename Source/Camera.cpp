#include "Camera.hpp"
#include "Vector2D.hpp"

using namespace Tin;

//Object Access
Camera* Camera::GetCurrentInstance() {
	return activeCamera;
}


//Position Access
Vector2D Camera::GetPosition() const {
	return *this->position;
}

Vector2D Camera::GetExtents() const {
	return *this->extents;
}


//Construction and Destruction
Camera::Camera(const uint16_t& w, const uint16_t& h) {
	uint16_t UPE = Vector2D::UnitPixelEquivalent;
	this->position = new Vector2D(0, 0);
	this->extents = new Vector2D(w/(2*UPE),h/(2*UPE));
}

Camera::~Camera() {
	delete this->position;
	delete this->extents;
}


//Statics
Camera* Camera::activeCamera;