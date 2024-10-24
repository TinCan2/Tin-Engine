#include "KeyboardManager.hpp"
#include <cstring>
#include <SDL.h>

using namespace Tin;

//Keyboard Access
bool KeyboardManager::KeyPressed(const char* const& keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (keyStates[scancode] && !keyBuffer[scancode]);
}

bool KeyboardManager::KeyDown(const char* const& keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return keyStates[scancode];
}

bool KeyboardManager::KeyReleased(const char* const& keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (!keyStates[scancode] && keyBuffer[scancode]);
}

const char* KeyboardManager::GetKey() {
	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++) {
		if (keyStates[i]) return SDL_GetKeyName(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(i)));
	}
	return "";
}


//Initialization and Clean Up
void KeyboardManager::Initialize() {
	keyStates = SDL_GetKeyboardState(nullptr);
	keyBuffer = new uint8_t[SDL_NUM_SCANCODES];
	std::memcpy(keyBuffer, keyStates, SDL_NUM_SCANCODES);
}

void KeyboardManager::CleanUp() {
	delete keyBuffer;
}


//Buffer Acces
void KeyboardManager::PushBuffer() {
	std::memcpy(keyBuffer, keyStates, SDL_NUM_SCANCODES);
}


//Statics
const uint8_t* KeyboardManager::keyStates;
uint8_t* KeyboardManager::keyBuffer;