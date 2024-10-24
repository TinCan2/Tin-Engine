#include "Animation.hpp"
#include "GameManager.hpp"
#include "Sprite.hpp"
#include "Vector2D.hpp"
#include <cstring>
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Sprite-Animation Demo", 640, 480);

	Sprite s(TIN_DEMO_LOCATION "Sprites/Colors.png");
	Animation a(TIN_DEMO_LOCATION "Sprites/Numbers.png", 32, 32, 10, Vector2D(2,0));

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		s.Draw(Vector2D(0,0));
		a.DrawFrame(Vector2D(0,0));
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}