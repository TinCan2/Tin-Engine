#include "Camera.hpp"
#include "Color.hpp"
#include "GameManager.hpp"
#include <SDL.h>

#ifdef TIN_MODULES_INCLUDE_FUNCTIONALS
	#include "FunctionalObject.hpp"
#endif

#ifdef TIN_MODULES_INCLUDE_INPUT
	#include "ControllerManager.hpp"
	#include "KeyboardManager.hpp"
	#include "MouseManager.hpp"
#endif

#ifdef TIN_MODULES_INCLUDE_PAINTER
	#include "Painter.hpp"
#endif

#ifdef TIN_MODULES_INCLUDE_PHYSICS
	#include "PhysicalObject.hpp"
#endif

#ifdef TIN_MODULES_INCLUDE_SPRITE
	#include "Sprite.hpp"
#endif

using namespace Tin;

//Singleton Implementation
GameManager* GameManager::Instantiate() {
	if (currentManager != nullptr) return nullptr;
	currentManager = new GameManager();
	return currentManager;
}

GameManager* GameManager::GetCurrentManager() {
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
	#ifdef TIN_MODULES_INCLUDE_INPUT
		ControllerManager::currentManager = new ControllerManager();
		KeyboardManager::currentManager = new KeyboardManager();
		MouseManager::currentManager = new MouseManager();
	#endif
	#ifdef TIN_MODULES_INCLUDE_PAINTER
		Painter::boundedRenderer = this->mainRenderer;
	#endif
	#ifdef TIN_MODULES_INCLUDE_SPRITE
		Sprite::boundedRenderer = this->mainRenderer;
	#endif
}

void GameManager::Handle() {
	if (this->resetColor) {
		SDL_SetRenderDrawColor(this->mainRenderer, this->backgroundColor->r, this->backgroundColor->g, this->backgroundColor->b, this->backgroundColor->a);
		this-> resetColor = false;
	}

	SDL_RenderClear(this->mainRenderer);

	#ifdef TIN_MODULES_INCLUDE_INPUT
		ControllerManager::GetCurrentManager()->PushBuffers();
		KeyboardManager::GetCurrentManager()->PushBuffer();
		MouseManager::GetCurrentManager()->PushBuffer();
	#endif

	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent)) {
		switch (currentEvent.type){
			case SDL_QUIT:
				this->QuitGame(); //This is temporary, to be later switched with a function pointer method.
				break;
			#ifdef TIN_MODULES_INCLUDE_INPUT
				case SDL_CONTROLLERDEVICEADDED:
					ControllerManager::GetCurrentManager()->AddController(currentEvent.cdevice.which);
					break;
				case SDL_CONTROLLERDEVICEREMOVED:
					ControllerManager::GetCurrentManager()->RemoveController(currentEvent.cdevice.which);
					break;
			#endif
		}
	}
}

void GameManager::Update() {
	#ifdef TIN_MODULES_INCLUDE_PHYSICS
		PhysicalObject::UpdateBodies();
	#endif

	#ifdef TIN_MODULES_INCLUDE_FUNCTIONALS
		FunctionalObject::UpdateObjects();
	#endif
}

void GameManager::Render() {
	SDL_RenderPresent(this->mainRenderer);
	this->frameCount++;
}

void GameManager::Terminate() {
	#ifdef TIN_MODULES_INCLUDE_INPUT
		delete ControllerManager::currentManager;
		delete KeyboardManager::currentManager;
		delete MouseManager::currentManager;
	#endif
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
uint64_t GameManager::GetFrameCount() const{
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