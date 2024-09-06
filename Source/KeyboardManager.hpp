#pragma once
#include "DllMacro.hpp"

namespace Tin {

	typedef unsigned char UInt8;

	class TIN_API KeyboardManager {
		public:
		static KeyboardManager* GetCurrentManager();

		KeyboardManager(const KeyboardManager& coppiedObject) = delete;

		bool KeyPressed(const char* keyName) const;
		bool KeyDown(const char* keyName) const;
		bool KeyReleased(const char* keyName) const;

		const char* GetLastKey() const;

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