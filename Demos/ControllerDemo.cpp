#include "ControllerManager.hpp"
#include "GameManager.hpp"
#include "Vector2D.hpp"
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Controller Demo", 640, 480);

	ControllerManager* controllerManager = ControllerManager::GetCurrentManager();

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();

		for (size_t i = 0; i < controllerManager->GetControllerCount(); i++) {
			std::cout << "Controller Number: " << i << std::endl;
			std::cout << "Button Y just pressed: " << controllerManager->ButtonPressed(i, ControllerManager::Buttons::Y) << std::endl;
			std::cout << "Right shoulder down: " << controllerManager->ButtonDown(i, ControllerManager::Buttons::RightShoulder) << std::endl;
			std::cout << "DpadUp released: " << controllerManager->ButtonReleased(i, ControllerManager::Buttons::DPadUp) << std::endl;
			std::cout << "Get button result: " << static_cast<int>(controllerManager->GetButton(i)) << std::endl;

			Vector2D rStick = controllerManager->GetStick(i, ControllerManager::Sides::Right);
			Vector2D lStick = controllerManager->GetStick(i, ControllerManager::Sides::Left);
			std::cout << "Right Stick: " << rStick.x << ";" << rStick.y << std::endl;
			std::cout << "Left Stick: " << lStick.x << ";" << lStick.y << std::endl;

			std::cout << "Right Trigger: " << controllerManager->GetTrigger(i, ControllerManager::Sides::Right) << std::endl;
			std::cout << "Left Trigger: " << controllerManager->GetTrigger(i, ControllerManager::Sides::Left) << std::endl;
			std::cout << std::endl;
		}

		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}