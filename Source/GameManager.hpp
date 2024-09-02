#pragma once
#include "DllMacro.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace Tin {
	struct Color;

	typedef unsigned int UInt16;
	typedef unsigned long long UInt64;

	class TIN_API GameManager{
		public:
		static GameManager* Instantiate();
		static GameManager* GetCurrentInstance();
		static void Destroy();

		GameManager(const GameManager&) = delete;

		void Initialize(const char* title, const UInt16& w, const UInt16& h);

		void Handle();
		void Update();
		void Render();

		void Terminate();

		bool IsQuitting() const;
		void QuitGame();

		UInt64 GetFrameCount() const;

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

		UInt64 frameCount;

		static GameManager* currentManager;
	};
}