#include "Keyboard.hpp"
#include <cstring>
#include <SDL.h>

using namespace Tin;

//Keyboard Access
bool Keyboard::KeyPressed(const char* const& keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (keyStates[scancode] && !keyBuffer[scancode]);
}

bool Keyboard::KeyDown(const char* const& keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return keyStates[scancode];
}

bool Keyboard::KeyReleased(const char* const& keyName) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(SDL_GetKeyFromName(keyName));
	return (!keyStates[scancode] && keyBuffer[scancode]);
}

const char* Keyboard::GetKey() {
	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++) {
		if (keyStates[i]) return SDL_GetKeyName(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(i)));
	}
	return "";
}


//Initialization and Clean Up
void Keyboard::Initialize() {
	keyStates = SDL_GetKeyboardState(nullptr);
	keyBuffer = new uint8_t[SDL_NUM_SCANCODES];
	std::memcpy(keyBuffer, keyStates, SDL_NUM_SCANCODES);
}

void Keyboard::CleanUp() {
	delete keyBuffer;
}


//Buffer Acces
void Keyboard::PushBuffer() {
	std::memcpy(keyBuffer, keyStates, SDL_NUM_SCANCODES);
}


//Statics
const uint8_t* Keyboard::keyStates;
uint8_t* Keyboard::keyBuffer;