#include "Camera.h"
#include "Vector2D.h"

//Object Access
Camera* Camera::GetCurrentInstance() {
	return activeCamera;
}


//Position Access
Vector2D Camera::GetPosition() {
	return *this->position;
}

Vector2D Camera::GetExtents() {
	return *this->extents;
}


//Construction and Destruction
Camera::Camera(UInt16 w, UInt16 h) {
	UInt16 UPE = Vector2D::UnitPixelEquivalent;
	this->position = new Vector2D(0, 0);
	this->extents = new Vector2D(w/(2*UPE),h/(2*UPE));
}

Camera::~Camera() {
	delete this->position;
	delete this->extents;
}


//Statics
Camera* Camera::activeCamera;