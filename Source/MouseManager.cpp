#include "Camera.hpp"
#include "MouseManager.hpp"
#include "Vector2D.hpp"
#include <SDL.h>

using namespace Tin;

//Singleton Implementation
MouseManager* MouseManager::GetCurrentManager() {
	return currentManager;
}


//Mouse Access
Vector2D MouseManager::GetMousePosition() const {
	int x, y;
	SDL_GetMouseState(&x, &y);

	float lX, lY;
	SDL_RenderWindowToLogical(this->mainRenderer, x, y, &lX, &lY);

	float UPE = Vector2D::UnitPixelEquivalent;
	Vector2D relativePos = Vector2D(lX/UPE, lY/UPE);

	Camera* camera = Camera::GetCurrentInstance();
	return camera->GetPosition() + camera->GetExtents().FlipH() + relativePos.FlipV();
}

bool MouseManager::ButtonPressed(const Buttons& button) {
	uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

	if (button == Buttons::None) return !mouseState && this->buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return (mouseState & buttonMask) && !(this->buttonBuffer & buttonMask);
}

bool MouseManager::ButtonDown(const Buttons& button) {
	uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

	if (button == Buttons::None) return !mouseState;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return mouseState & buttonMask;
}

bool MouseManager::ButtonReleased(const Buttons& button) {
	uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

	if (button == Buttons::None) return mouseState && !this->buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return (mouseState & buttonMask) && !(this->buttonBuffer & buttonMask);
}

MouseManager::Buttons MouseManager::GetButton() {
	for (size_t i = 0; i < 5; i++) {
		Buttons currentButton = static_cast<Buttons>(i);
		if(ButtonDown(currentButton)) return currentButton;
	}
	return Buttons::None;
}

//Construction and Destruction
MouseManager::MouseManager() {}

MouseManager::~MouseManager() {}


//Buffer Access
void MouseManager::PushBuffer() {
	this->buttonBuffer = SDL_GetMouseState(nullptr, nullptr);
}


//Statics
MouseManager* MouseManager::currentManager;