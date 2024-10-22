#include "GameManager.hpp"
#include "Sprite.hpp"
#include "Vector2D.hpp"

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Sprite Demo", 640, 480);

	Sprite s(TIN_DEMO_LOCATION "Sprites/Colors.png");

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		s.Draw(Vector2D(0,0));
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}