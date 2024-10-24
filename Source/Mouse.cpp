#include "Camera.hpp"
#include "Mouse.hpp"
#include "Vector2D.hpp"
#include <SDL.h>

using namespace Tin;

//Mouse Access
Vector2D Mouse::GetMousePosition() {
	int x, y;
	SDL_GetMouseState(&x, &y);

	float lX, lY;
	SDL_RenderWindowToLogical(boundRenderer, x, y, &lX, &lY);

	float UPE = Vector2D::UnitPixelEquivalent;
	Vector2D relativePos = Vector2D(lX/UPE, lY/UPE);

	Camera* camera = Camera::GetCurrentInstance();
	return camera->GetPosition() + camera->GetExtents().FlipH() + relativePos.FlipV();
}

bool Mouse::ButtonPressed(const Buttons& button) {
	uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

	if (button == Buttons::None) return !mouseState && buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return (mouseState & buttonMask) && !(buttonBuffer & buttonMask);
}

bool Mouse::ButtonDown(const Buttons& button) {
	uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

	if (button == Buttons::None) return !mouseState;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return mouseState & buttonMask;
}

bool Mouse::ButtonReleased(const Buttons& button) {
	uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

	if (button == Buttons::None) return mouseState && !buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return (mouseState & buttonMask) && !(buttonBuffer & buttonMask);
}

Mouse::Buttons Mouse::GetButton() {
	for (size_t i = 0; i < 5; i++) {
		Buttons currentButton = static_cast<Buttons>(i);
		if(ButtonDown(currentButton)) return currentButton;
	}
	return Buttons::None;
}

//Buffer Access
void Mouse::PushBuffer() {
	buttonBuffer = SDL_GetMouseState(nullptr, nullptr);
}


//Statics
uint32_t Mouse::buttonBuffer;
SDL_Renderer* Mouse::boundRenderer;