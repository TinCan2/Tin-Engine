#pragma once
#include "DllMacro.hpp"
#include <cstdint>

namespace Tin {

	class TIN_API KeyboardManager {
		public:
		static KeyboardManager* GetCurrentManager();

		KeyboardManager(const KeyboardManager& coppiedObject) = delete;

		bool KeyPressed(const char* const& keyName) const;
		bool KeyDown(const char* const& keyName) const;
		bool KeyReleased(const char* const& keyName) const;

		const char* GetKey() const;

		private:
		KeyboardManager();
		~KeyboardManager();

		friend class GameManager;

		void PushBuffer();

		const uint8_t* keyStates;
		uint8_t* keyBuffer;

		static KeyboardManager* currentManager;
	};
}