#include "Gamepads.hpp"
#include "Vector2D.hpp"
#include <algorithm>
#include <SDL2/SDL.h>
#include <stdexcept>

using namespace Tin;

//Gamepad Access
size_t Gamepads::GetGamepadCount() {
	return gamepadList.size();
}

bool Gamepads::ButtonPressed(const size_t& index, const Buttons& button) {
	uint32_t buttonStates = FormatButtons(index);
	uint32_t buttonBuffer = gamepadList[index].buttonBuffer;

	if (button == Buttons::None) return !buttonStates && buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return (buttonStates & buttonMask) && !(buttonBuffer & buttonMask);
}

bool Gamepads::ButtonDown(const size_t& index, const Buttons& button) {
	uint32_t buttonStates = FormatButtons(index);

	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return buttonStates & buttonMask;
}

bool Gamepads::ButtonReleased(const size_t& index, const Buttons& button) {
	uint32_t buttonStates = FormatButtons(index);
	uint32_t buttonBuffer = gamepadList[index].buttonBuffer;

	if (button == Buttons::None) return !buttonStates && buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return !(buttonStates & buttonMask) && (buttonBuffer & buttonMask);
}

Gamepads::Buttons Gamepads::GetButton(const size_t& index) {
	for (size_t i = 0; i <= 20; i++) {
		Buttons currentButton = static_cast<Buttons>(i);
		if(ButtonDown(index, currentButton)) return currentButton;
	}
	return Buttons::None;
}

Vector2D Gamepads::GetStick(const size_t& index, const Sides& side) {
	if (index >= gamepadList.size()) throw std::runtime_error("The requested gamepad does not exist.");
	SDL_GameController* gamepad = gamepadList[index].controller;

	bool right = (side == Sides::Right);
	int16_t x = SDL_GameControllerGetAxis(gamepad, right ? SDL_CONTROLLER_AXIS_RIGHTX : SDL_CONTROLLER_AXIS_LEFTX);
	int16_t y = SDL_GameControllerGetAxis(gamepad, right ? SDL_CONTROLLER_AXIS_RIGHTY : SDL_CONTROLLER_AXIS_LEFTY);

	return Vector2D(static_cast<float>(x)/INT16_MAX, static_cast<float>(y)/INT16_MAX);
}

float Gamepads::GetTrigger(const size_t& index, const Sides& side) {
    if (index >= gamepadList.size()) throw std::runtime_error("The requested gamepad does not exist.");
	SDL_GameController* gamepad = gamepadList[index].controller;

	bool right = (side == Sides::Right);
	int v = SDL_GameControllerGetAxis(gamepad, right ? SDL_CONTROLLER_AXIS_TRIGGERRIGHT : SDL_CONTROLLER_AXIS_TRIGGERLEFT);

	return static_cast<float>(v)/INT16_MAX;
}


//Gamepad List Access
void Gamepads::RemoveAllGamepads() {
	for(GamepadInfo& it : gamepadList) SDL_GameControllerClose(it.controller);
	gamepadList.clear();
}

void Gamepads::AddGamepad(const int32_t& deviceIndex) {
	gamepadList.push_back({SDL_GameControllerOpen(deviceIndex), 0});
}

void Gamepads::RemoveGamepad(const int32_t& instanceID) {
	auto lam = [&instanceID](const GamepadInfo& x) {
		return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(x.controller)) == instanceID;
	};
	std::vector<GamepadInfo>::iterator it = std::find_if(gamepadList.begin(), gamepadList.end(), lam);

	SDL_GameControllerClose(it->controller);
	gamepadList.erase(it);
}


//Buffer Access
void Gamepads::PushBuffers() {
	for (size_t i = 0; i < gamepadList.size(); i++) gamepadList[i].buttonBuffer = FormatButtons(i);
}


//Format Helpers
uint32_t Gamepads::FormatButtons(const size_t& index) {
	if (index >= gamepadList.size()) throw std::runtime_error("The requested gamepad does not exist.");
	SDL_GameController* gamepad = gamepadList[index].controller;

	uint32_t output = 0;
	size_t i = 21;
	while (i > 0) {
		output <<= 1;
		output |= SDL_GameControllerGetButton(gamepad, static_cast<SDL_GameControllerButton>(i-1));
		i--;
	}
	return output;
}


//Statics
std::vector<Gamepads::GamepadInfo> Gamepads::gamepadList;