#pragma once
#include "DllMacro.hpp"
#include <cstdint>
#include <vector>

typedef struct _SDL_GameController SDL_GameController;

namespace Tin {

	struct Vector2D;

	class TIN_API ControllerManager {
		public:
		ControllerManager() = delete;
		~ControllerManager() = delete;

		enum class Buttons {A, B, X, Y, Back, Guide, Start, LeftStick, RightStick, LeftShoulder, RightShoulder, DPadUp, DPadDown,
							DPadLeft, DPadRight, Misc, Paddle1, Paddle3, Paddle2, Paddle4, Touchpad, None};

		enum class Sides {Left, Right};

		static size_t GetControllerCount();

		static bool ButtonPressed(const size_t& index, const Buttons& button);
		static bool ButtonDown(const size_t& index, const Buttons& button);
		static bool ButtonReleased(const size_t& index, const Buttons& button);

		static Buttons GetButton(const size_t& index);

		static Vector2D GetStick(const size_t& index, const Sides& side);
		static float GetTrigger(const size_t& index, const Sides& side);

		private:
		static void RemoveAllControllers();

		static void AddController(const int32_t& deviceIndex);
		static void RemoveController(const int32_t& instanceID);

		static void PushBuffers();

		friend class GameManager;

		static uint32_t FormatButtons(const size_t& index);

		struct ControllerInfo {SDL_GameController* controller; uint32_t buttonBuffer;};

		static std::vector<ControllerInfo> controllerList;
	};
}