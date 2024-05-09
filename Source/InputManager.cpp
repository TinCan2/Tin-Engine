#include "InputManager.h"
#include <SDL2/SDL.h>

using namespace Tin;

//Singleton Implementation
InputManager* InputManager::GetCurrentManager() {
	return currentManager;
}


//Keyboard Access
bool InputManager::GetKeyState(Keys targetKey) {
	return this->keyStates[(int)targetKey];
}


//Construction and Destruction
InputManager::InputManager() {
	this->keyStates = SDL_GetKeyboardState(nullptr);
}

InputManager::~InputManager() {}


//Statics
InputManager* InputManager::currentManager;