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
		std::cout << "The following key is pressed: " << keyboardManager->GetKey() << std::endl;
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}