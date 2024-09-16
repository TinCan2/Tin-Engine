#include "ControllerManager.hpp"
#include "Vector2D.hpp"
#include <algorithm>
#include <SDL.h>
#include <stdexcept>

#include <iostream>

using namespace Tin;

//Singleton Implementation
ControllerManager* ControllerManager::GetCurrentManager() {
	return currentManager;
}


//Controller Access
size_t ControllerManager::GetControllerCount() {
	return this->controllerList.size();
}

bool ControllerManager::ButtonPressed(const size_t& index, const Buttons& button) const {
	uint32_t buttonStates = this->FormatButtons(index);
	uint32_t buttonBuffer = this->controllerList[index]->buttonBuffer;

	if (button == Buttons::None) return !buttonStates && buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return (buttonStates & buttonMask) && !(buttonBuffer & buttonMask);
}

bool ControllerManager::ButtonDown(const size_t& index, const Buttons& button) const {
	uint32_t buttonStates = this->FormatButtons(index);

	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return buttonStates & buttonMask;
}

bool ControllerManager::ButtonReleased(const size_t& index, const Buttons& button) const {
	uint32_t buttonStates = this->FormatButtons(index);
	uint32_t buttonBuffer = this->controllerList[index]->buttonBuffer;

	if (button == Buttons::None) return !buttonStates && buttonBuffer;
	uint32_t buttonMask = 1 << static_cast<uint32_t>(button);
	return !(buttonStates & buttonMask) && (buttonBuffer & buttonMask);
}

ControllerManager::Buttons ControllerManager::GetButton(const size_t& index) const {
	for (size_t i = 0; i <= 20; i++) {
		Buttons currentButton = static_cast<Buttons>(i);
		if(this->ButtonDown(index, currentButton)) return currentButton;
	}
	return Buttons::None;
}

Vector2D ControllerManager::GetStick(const size_t& index, const Sides& side) const {
	if (index >= this->controllerList.size()) throw std::runtime_error("The requested controller does not exist.");
	SDL_GameController* controller = this->controllerList[index]->controller;

	bool right = (side == Sides::Right);
	int16_t x = SDL_GameControllerGetAxis(controller, right ? SDL_CONTROLLER_AXIS_RIGHTX : SDL_CONTROLLER_AXIS_LEFTX);
	int16_t y = SDL_GameControllerGetAxis(controller, right ? SDL_CONTROLLER_AXIS_RIGHTY : SDL_CONTROLLER_AXIS_LEFTY);

	return Vector2D(static_cast<float>(x)/INT16_MAX, static_cast<float>(y)/INT16_MAX);
}

float ControllerManager::GetTrigger(const size_t& index, const Sides& side) const {
    if (index >= this->controllerList.size()) throw std::runtime_error("The requested controller does not exist.");
	SDL_GameController* controller = this->controllerList[index]->controller;

	bool right = (side == Sides::Right);
	int v = SDL_GameControllerGetAxis(controller, right ? SDL_CONTROLLER_AXIS_TRIGGERRIGHT : SDL_CONTROLLER_AXIS_TRIGGERLEFT);

	return static_cast<float>(v)/INT16_MAX;
}


//Construction and Destruction
ControllerManager::ControllerManager() {}

ControllerManager::~ControllerManager() {}


//Controller List Access
void ControllerManager::AddController(const int32_t& deviceIndex) {
	this->controllerList.push_back(new ControllerInfo());
	this->controllerList.back()->controller = SDL_GameControllerOpen(deviceIndex);
	this->controllerList.back()->buttonBuffer = 0;
}

void ControllerManager::RemoveController(const int32_t& instanceID) {
	auto lam = [&instanceID](ControllerInfo* x) {
		return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(x->controller)) == instanceID;
	};
	std::vector<ControllerInfo*>::iterator it = std::find_if(this->controllerList.begin(), this->controllerList.end(), lam);
	ControllerInfo* info = *it;

	SDL_GameControllerClose(info->controller);
	delete info;
	this->controllerList.erase(it);
}


//Format Helpers
uint32_t ControllerManager::FormatButtons(const size_t& index) const {
	if (index >= this->controllerList.size()) throw std::runtime_error("The requested controller does not exist.");
	SDL_GameController* controller = this->controllerList[index]->controller;

	uint32_t output = 0;
	size_t i = 21;
	while (i > 0) {
		output <<= 1;
		output |= SDL_GameControllerGetButton(controller, static_cast<SDL_GameControllerButton>(i-1));
		i--;
	}
	return output;
}


//Buffer Access
void ControllerManager::PushBuffers() {
	for (size_t i = 0; i < this->controllerList.size(); i++) controllerList[i]->buttonBuffer = this->FormatButtons(i);
}


//Statics
ControllerManager* ControllerManager::currentManager;