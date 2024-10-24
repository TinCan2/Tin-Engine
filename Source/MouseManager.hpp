#pragma once
#include "DllMacro.hpp"
#include <cstdint>

namespace Tin {

	struct Vector2D;

	class TIN_API MouseManager {
		public:
		MouseManager() = delete;
		~MouseManager() = delete;

		enum class Buttons {Left, Middle, Right, SideBack, SideFront, None};

		static Vector2D GetMousePosition();

		static bool ButtonPressed(const Buttons& button);
		static bool ButtonDown(const Buttons& button);
		static bool ButtonReleased(const Buttons& button);

		static Buttons GetButton();

		private:
		static void PushBuffer();
		friend class GameManager;

		static uint32_t buttonBuffer;
	};
}