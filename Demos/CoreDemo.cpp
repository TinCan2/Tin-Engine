#include "GameManager.hpp"

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Core Demo", 640, 480);

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}