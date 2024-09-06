#include "GameManager.hpp"
#include "FunctionalObject.hpp"

#include <iostream>

using namespace Tin;

class DemoFunctional : public FunctionalObject {
	public:
	virtual void OnUpdate() override {
		std::cout << "This is the method of the demo functional." << std::endl;
	}
};

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Core Demo", 640, 480);

	DemoFunctional d;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}