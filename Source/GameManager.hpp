#pragma once
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

namespace Tin {
	struct Color;

	class GameManager{
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

		Color GetRenderColor() const;
		void ScheduleColorReset();

		private:
		GameManager();
		~GameManager();

		SDL_Window* gameWindow;
		SDL_Renderer* mainRenderer;

		bool quitting;

		Color* renderColor;
		bool resetColor;

		uint64_t frameCount;

		static GameManager* currentManager;
	};
}