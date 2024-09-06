#include "GameManager.hpp"
#include "KeyboardManager.hpp"
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Input Demo", 640, 480);

	KeyboardManager* keyboardManager = KeyboardManager::GetCurrentManager();

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		if(keyboardManager->KeyPressed("a")) std::cout << "The key a was pressed." << std::endl;
		if(keyboardManager->KeyDown("a")) std::cout << "The key a is down." << std::endl;
		if(keyboardManager->KeyReleased("a")) std::cout << "The key a was released." << std::endl;
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}