#include "Camera.hpp"
#include "MouseManager.hpp"
#include "Vector2D.hpp"
#include <SDL.h>

#include <iostream>

using namespace Tin;

//Singleton Implementation
MouseManager* MouseManager::GetCurrentInstance() {
	return currentManager;
}


//Mouse Access
Vector2D MouseManager::GetMousePosition() const {
	int x, y;
	SDL_GetMouseState(&x, &y);

	float UPE = Vector2D::UnitPixelEquivalent;
	Vector2D relativePos = Vector2D(x/UPE, y/UPE);

	Camera* camera = Camera::GetCurrentInstance();
	return camera->GetPosition() + camera->GetExtents().FlipH() + relativePos.FlipV();
}


//Construction and Destruction
MouseManager::MouseManager() {}

MouseManager::~MouseManager() {}


//Statics
MouseManager* MouseManager::currentManager;