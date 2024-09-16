#pragma once
#include "DllMacro.hpp"
#include <cstdint>
#include <vector>

typedef struct _SDL_GameController SDL_GameController;

namespace Tin {

	struct Vector2D;

	class TIN_API ControllerManager {
		public:
		static ControllerManager* GetCurrentManager();

		ControllerManager(const ControllerManager& coppiedObject) = delete;

		enum class Buttons {A, B, X, Y, Back, Guide, Start, LeftStick, RightStick, LeftShoulder, RightShoulder, DPadUp, DPadDown,
							DPadLeft, DPadRight, Misc, Paddle1, Paddle3, Paddle2, Paddle4, Touchpad, None};

		enum class Sides {Left, Right};

		size_t GetControllerCount();

		bool ButtonPressed(const size_t& index, const Buttons& button) const;
		bool ButtonDown(const size_t& index, const Buttons& button) const;
		bool ButtonReleased(const size_t& index, const Buttons& button) const;

		Buttons GetButton(const size_t& index) const;

		Vector2D GetStick(const size_t& index, const Sides& side) const;
		float GetTrigger(const size_t& index, const Sides& side) const;

		private:
		ControllerManager();
		~ControllerManager();

		friend class GameManager;

		void AddController(const int32_t& deviceIndex);
		void RemoveController(const int32_t& instanceID);

		uint32_t FormatButtons(const size_t& index) const;

		void PushBuffers();

		struct ControllerInfo {
			SDL_GameController* controller;
			uint32_t buttonBuffer;
		};

		std::vector<ControllerInfo*> controllerList;

		static ControllerManager* currentManager;
	};
}