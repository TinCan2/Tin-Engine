#pragma once
#include "DllMacro.hpp"
#include <cstdint>

namespace Tin {

	class TIN_API KeyboardManager {
		public:
		KeyboardManager() = delete;
		~KeyboardManager() = delete;

		static bool KeyPressed(const char* const& keyName);
		static bool KeyDown(const char* const& keyName);
		static bool KeyReleased(const char* const& keyName);

		static const char* GetKey();

		private:
		static void Initialize();
		static void CleanUp();

		static void PushBuffer();
		friend class GameManager;

		static const uint8_t* keyStates;
		static uint8_t* keyBuffer;
	};
}