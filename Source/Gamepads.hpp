#pragma once
#include "DllMacro.hpp"
#include <cstdint>
#include <vector>

typedef struct _SDL_GameController SDL_GameController;

namespace Tin {

	struct Vector2D;

	class TIN_API Gamepads {
		public:
		Gamepads() = delete;
		~Gamepads() = delete;

		enum class Buttons {A, B, X, Y, Back, Guide, Start, LeftStick, RightStick, LeftShoulder, RightShoulder, DPadUp, DPadDown,
							DPadLeft, DPadRight, Misc, Paddle1, Paddle3, Paddle2, Paddle4, Touchpad, None};

		enum class Sides {Left, Right};

		static size_t GetGamepadCount();

		static bool ButtonPressed(const size_t& index, const Buttons& button);
		static bool ButtonDown(const size_t& index, const Buttons& button);
		static bool ButtonReleased(const size_t& index, const Buttons& button);

		static Buttons GetButton(const size_t& index);

		static Vector2D GetStick(const size_t& index, const Sides& side);
		static float GetTrigger(const size_t& index, const Sides& side);

		private:
		static void RemoveAllGamepads();

		static void AddGamepad(const int32_t& deviceIndex);
		static void RemoveGamepad(const int32_t& instanceID);

		static void PushBuffers();

		friend class GameManager;

		static uint32_t FormatButtons(const size_t& index);

		struct GamepadInfo {SDL_GameController* controller; uint32_t buttonBuffer;};

		static std::vector<GamepadInfo> gamepadList;
	};
}