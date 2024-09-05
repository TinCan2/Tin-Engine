#pragma once
#include "DllMacro.hpp"

namespace Tin {

	struct Vector2D;

	class TIN_API MouseManager {
		public:
		static MouseManager* GetCurrentInstance();

		MouseManager(const MouseManager&) = delete;

		Vector2D GetMousePosition() const;

		private:
		MouseManager();
		~MouseManager();

		friend class GameManager;

		static MouseManager* currentManager;
	};
}