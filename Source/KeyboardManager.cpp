#include "KeyboardManager.hpp"
#include <cstring>
#include <SDL.h>


using namespace Tin;

//Singleton Implementation
KeyboardManager* KeyboardManager::GetCurrentManager() {
	return currentManager;
}


//Construction and Destruction
KeyboardManager::KeyboardManager() {
	this->keyStates = SDL_GetKeyboardState(nullptr);
	this->keyBuffer = new UInt8[SDL_NUM_SCANCODES];
	std::memcpy(this->keyBuffer, this->keyStates, SDL_NUM_SCANCODES*sizeof(UInt8));
}

KeyboardManager::~KeyboardManager() {}


//Keyboard Access
bool KeyboardManager::KeyPressed(const char* keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (this->keyStates[scancode] && !this->keyBuffer[scancode]);
}

bool KeyboardManager::KeyDown(const char* keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return this->keyStates[scancode];
}

bool KeyboardManager::KeyReleased(const char* keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (!this->keyStates[scancode] && this->keyBuffer[scancode]);
}


//Buffer Acces
void KeyboardManager::PushBuffer() {
	std::memcpy(this->keyBuffer, this->keyStates, SDL_NUM_SCANCODES*sizeof(UInt8));
}


//Statics
KeyboardManager* KeyboardManager::currentManager;