#include "Camera.h"
#include "GameManager.h"
#include "Sprite.h"
#include <SDL2/SDL.h>

//Singleton Implementation
GameManager* GameManager::Instantiate(){
	if (currentManager != nullptr) return nullptr;
	currentManager = new GameManager();
	return currentManager;
}

GameManager* GameManager::GetCurrentInstance(){
	return currentManager;
}

void GameManager::Destroy(){
	if (currentManager != nullptr) delete currentManager;
}


//Game Events
void GameManager::Initialize(const char* title, UInt16 w, UInt16 h) {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	this->mainRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_PRESENTVSYNC |  SDL_RENDERER_ACCELERATED);

	Camera::activeCamera = new Camera(w, h);
	Sprite::boundedRenderer = this->mainRenderer;
}

void GameManager::Handle() {
	SDL_RenderClear(this->mainRenderer);

	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent)) {
		switch (currentEvent.type){
			case SDL_QUIT:
				this->QuitGame(); //This is temporary
				break;
		}
	}
}

void GameManager::Update() {}

void GameManager::Render() {
	SDL_RenderPresent(this->mainRenderer);
	this->frameCount++;
}

void GameManager::Terminate() {
	delete Camera::activeCamera;

	SDL_DestroyRenderer(this->mainRenderer);
	SDL_DestroyWindow(this->gameWindow);
	SDL_Quit();
}


//Quitting
bool GameManager::IsQuitting() {
	return this->quitting;
}

void GameManager::QuitGame() {
	this->quitting = true;
}


//Frames
UInt64 GameManager::GetFrameCount() {
	return this->frameCount;
}


//Construction and Destruction
GameManager::GameManager() {
	this->quitting = false;
	this->frameCount = 0;
}

GameManager::~GameManager() {}


//Statics
GameManager* GameManager::currentManager;