#include "GameManager.hpp"
#include <map>

using namespace Tin;

class SceneManager {
	std::map<
}

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Scene Manager Demo", 640, 480);

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}