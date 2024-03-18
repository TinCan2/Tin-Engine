#include "InputManager.h"
#include <SDL2/SDL.h>

//Singleton Implementation
InputManager* InputManager::GetCurrentManager() {
	return currentManager;
}


//Key Access
bool InputManager::GetKeyState(Keys targetKey) {
	return this->KeyStates[(int)targetKey];
}

void InputManager::UpdateKeyStates() {
	this->KeyStates = SDL_GetKeyboardState(nullptr);
}


//Construction and Destruction
InputManager::InputManager() {
	this->UpdateKeyStates();
}

InputManager::~InputManager() {}


//Statics
InputManager* InputManager::currentManager = nullptr;