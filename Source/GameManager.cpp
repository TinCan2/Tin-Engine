#include "Camera.hpp"
#include "Color.hpp"
#include "GameManager.hpp"
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
void GameManager::Initialize(const char* title, const uint16_t& w, const uint16_t& h) {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	this->mainRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_PRESENTVSYNC |  SDL_RENDERER_ACCELERATED);

	Camera::activeCamera = new Camera(w, h);
}

void GameManager::Handle() {
	if (this->resetColor) {
		SDL_SetRenderDrawColor(this->mainRenderer, this->renderColor->r, this->renderColor->g, this->renderColor->b, this->renderColor->a);
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
uint64_t GameManager::GetFrameCount() const {
	return this->frameCount;
}


//Color Acces
Color GameManager::GetRenderColor() const {
	return *this->renderColor;
}

void GameManager::ScheduleColorReset() {
	this->resetColor = true;
}


//Construction and Destruction
GameManager::GameManager() {
	this->quitting = false;
	this->frameCount = 0;
	this->renderColor = new Color();
}

GameManager::~GameManager() {
	delete this->renderColor;
}


//Statics
GameManager* GameManager::currentManager;