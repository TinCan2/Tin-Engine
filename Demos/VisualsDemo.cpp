#include "Animation.hpp"
#include "GameManager.hpp"
#include "Sprite.hpp"
#include "VisualObject.hpp"
#include "Vector2D.hpp"
#include "MouseManager.hpp"

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Visuals Demo", 640, 480);

	MouseManager* mouseManager = MouseManager::GetCurrentManager();

	Sprite s(TIN_DEMO_LOCATION "Sprites/Colors.png", Vector2D(1,1));
	Animation a(TIN_DEMO_LOCATION "Sprites/Numbers.png", 32, 32, 10, Vector2D(1,1));

	VisualObject front(Vector2D(0,0), -1);
	VisualObject back(Vector2D(0,0), 1);

	front.SetVisual(a);
	back.SetVisual(s);

	bool switched = false;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		if (mouseManager->ButtonPressed(MouseManager::Buttons::Left)) {
			if (!switched) {
				front.SetVisual(s);
				back.SetVisual(a);
			}
			else {
				front.SetVisual(a);
				back.SetVisual(s);
			}

			switched = !switched;
		}

		front.SetPosition(mouseManager->GetMousePosition());
		back.SetPosition(-mouseManager->GetMousePosition());
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}