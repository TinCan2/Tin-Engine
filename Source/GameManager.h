#pragma once

struct SDL_Window;
struct SDL_Renderer;
struct Color;

typedef unsigned int UInt16;
typedef unsigned long long UInt64;

class GameManager{
	public:
	static GameManager* Instantiate();
	static GameManager* GetCurrentInstance();
	static void Destroy();

	GameManager(const GameManager&) = delete;

	void Initialize(const char* title, UInt16 w, UInt16 h);
	void Handle();
	void Update();
	void Render();
	void Terminate();

	bool IsQuitting();
	void QuitGame();

	UInt64 GetFrameCount();

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

	UInt64 frameCount;

	static GameManager* currentManager;
};