#include "Gamepads.hpp"
#include "GameManager.hpp"
#include "Vector2D.hpp"
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Controller Demo", 640, 480);

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();

		for (size_t i = 0; i < Gamepads::GetGamepadCount(); i++) {
			std::cout << "Controller Number: " << i << std::endl;
			std::cout << "Button Y just pressed: " << Gamepads::ButtonPressed(i, Gamepads::Buttons::Y) << std::endl;
			std::cout << "Right shoulder down: " << Gamepads::ButtonDown(i, Gamepads::Buttons::RightShoulder) << std::endl;
			std::cout << "DpadUp released: " << Gamepads::ButtonReleased(i, Gamepads::Buttons::DPadUp) << std::endl;
			std::cout << "Get button result: " << static_cast<int>(Gamepads::GetButton(i)) << std::endl;

			Vector2D rStick = Gamepads::GetStick(i, Gamepads::Sides::Right);
			Vector2D lStick = Gamepads::GetStick(i, Gamepads::Sides::Left);
			std::cout << "Right Stick: " << rStick.x << ";" << rStick.y << std::endl;
			std::cout << "Left Stick: " << lStick.x << ";" << lStick.y << std::endl;

			std::cout << "Right Trigger: " << Gamepads::GetTrigger(i, Gamepads::Sides::Right) << std::endl;
			std::cout << "Left Trigger: " << Gamepads::GetTrigger(i, Gamepads::Sides::Left) << std::endl;
			std::cout << std::endl;
		}

		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}