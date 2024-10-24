#include "GameManager.hpp"
#include "Keyboard.hpp"
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Input Demo", 640, 480);

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		if(Keyboard::KeyPressed("a")) std::cout << "The key a was pressed." << std::endl;
		if(Keyboard::KeyDown("a")) std::cout << "The key a is down." << std::endl;
		if(Keyboard::KeyReleased("a")) std::cout << "The key a was released." << std::endl;
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}