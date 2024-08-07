#include "Camera.h"
#include "Color.h"
#include "Painter.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Sprite.h"
#include <SDL2/SDL.h>

using namespace Tin;

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
void GameManager::Initialize(const char* title, const UInt16& w, const UInt16& h) {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	this->mainRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_PRESENTVSYNC |  SDL_RENDERER_ACCELERATED);

	Camera::activeCamera = new Camera(w, h);
	Painter::boundedRenderer = this->mainRenderer;
	InputManager::currentManager = new InputManager();
	Sprite::boundedRenderer = this->mainRenderer;
}

void GameManager::Handle() {
	if (this->resetColor) {
		SDL_SetRenderDrawColor(this->mainRenderer, this->backgroundColor->r, this->backgroundColor->g, this->backgroundColor->b, this->backgroundColor->a);
		this-> resetColor = false;
	}

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
	delete InputManager::currentManager;
	delete Camera::activeCamera;

	SDL_DestroyRenderer(this->mainRenderer);
	SDL_DestroyWindow(this->gameWindow);
	SDL_Quit();
}


//Quitting
bool GameManager::IsQuitting() const {
	return this->quitting;
}

void GameManager::QuitGame() {
	this->quitting = true;
}


//Frames
UInt64 GameManager::GetFrameCount() const{
	return this->frameCount;
}


//Color Access
Color GameManager::GetBackgroundColor() const {
	return *this->backgroundColor;
}

void GameManager::ScheduleColorReset() {
	this->resetColor = true;
}


//Construction and Destruction
GameManager::GameManager() {
	this->quitting = false;
	this->frameCount = 0;
	this->backgroundColor = new Color();
}

GameManager::~GameManager() {
	delete this->backgroundColor;
}


//Statics
GameManager* GameManager::currentManager;