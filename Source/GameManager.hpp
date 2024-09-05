#pragma once
#include "DllMacro.hpp"
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

namespace Tin {
	struct Color;

	class TIN_API GameManager{
		public:
		static GameManager* Instantiate();
		static GameManager* GetCurrentInstance();
		static void Destroy();

		GameManager(const GameManager&) = delete;

		void Initialize(const char* title, const uint16_t& w, const uint16_t& h);

		void Handle();
		void Update();
		void Render();

		void Terminate();

		bool IsQuitting() const;
		void QuitGame();

		uint64_t GetFrameCount() const;

		Color GetBackgroundColor() const;
		void ScheduleColorReset();

		private:
		GameManager();
		~GameManager();

		SDL_Window* gameWindow;
		SDL_Renderer* mainRenderer;

		bool quitting;

		Color* backgroundColor;
		bool resetColor;

		uint64_t frameCount;

		static GameManager* currentManager;
	};
}