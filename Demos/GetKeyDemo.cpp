#include "GameManager.hpp"
#include "Keyboard.hpp"
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Get Key Demo", 640, 480);

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		std::cout << "The following key is pressed: " << Keyboard::GetKey() << std::endl;
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}