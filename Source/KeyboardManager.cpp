#include "KeyboardManager.hpp"
#include <cstring>
#include <SDL.h>


using namespace Tin;

//Singleton Implementation
KeyboardManager* KeyboardManager::GetCurrentManager() {
	return currentManager;
}


//Keyboard Access
bool KeyboardManager::KeyPressed(const char* const& keyName) const {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (this->keyStates[scancode] && !this->keyBuffer[scancode]);
}

bool KeyboardManager::KeyDown(const char* const& keyName) const {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return this->keyStates[scancode];
}

bool KeyboardManager::KeyReleased(const char* const& keyName) const {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (!this->keyStates[scancode] && this->keyBuffer[scancode]);
}

const char* KeyboardManager::GetLastKey() const {
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		if (this->keyStates[i]) return SDL_GetKeyName(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(i)));
	}
	return "";
}


//Construction and Destruction
KeyboardManager::KeyboardManager() {
	this->keyStates = SDL_GetKeyboardState(nullptr);
	this->keyBuffer = new UInt8[SDL_NUM_SCANCODES];
	std::memcpy(this->keyBuffer, this->keyStates, SDL_NUM_SCANCODES*sizeof(UInt8));
}

KeyboardManager::~KeyboardManager() {}


//Buffer Acces
void KeyboardManager::PushBuffer() {
	std::memcpy(this->keyBuffer, this->keyStates, SDL_NUM_SCANCODES*sizeof(UInt8));
}


//Statics
KeyboardManager* KeyboardManager::currentManager;