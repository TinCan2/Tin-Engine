#pragma once
#include "DllMacro.hpp"
#include <cstdint>

namespace Tin {

	struct Vector2D;

	class TIN_API MouseManager {
		public:
		static MouseManager* GetCurrentInstance();

		MouseManager(const MouseManager&) = delete;

		enum class Buttons {Left, Middle, Right, SideBack, SideFront, None};

		Vector2D GetMousePosition() const;

		bool ButtonPressed(Buttons button);
		bool ButtonDown(Buttons button);
		bool ButtonReleased(Buttons button);

		Buttons GetLastButton();

		private:
		MouseManager();
		~MouseManager();

		friend class GameManager;

		uint32_t buttonBuffer;
		void PushBuffer();

		static MouseManager* currentManager;
	};
}