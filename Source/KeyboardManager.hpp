#pragma once
#include "DllMacro.hpp"

namespace Tin {

	typedef unsigned char UInt8;

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

		const UInt8* keyStates;
		UInt8* keyBuffer;

		static KeyboardManager* currentManager;
	};
}