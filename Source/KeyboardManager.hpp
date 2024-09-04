#pragma once
#include "DllMacro.hpp"

namespace Tin {

	typedef unsigned char UInt8;

	class TIN_API KeyboardManager {
		public:
		static KeyboardManager* GetCurrentManager();

		KeyboardManager(const KeyboardManager& coppiedObject) = delete;
		KeyboardManager operator=(const KeyboardManager& coppiedObject) = delete;

		bool KeyPressed(const char* keyName);
		bool KeyDown(const char* keyName);
		bool KeyReleased(const char* keyName);

		private:
		KeyboardManager();
		~KeyboardManager();

		friend class GameManager;

		void PushBuffer();

		const UInt8* keyStates;
		UInt8* keyBuffer;

		static KeyboardManager* currentManager;
	};
}