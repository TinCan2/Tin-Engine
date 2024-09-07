#include "GameManager.hpp"
#include "Painter.hpp"
#include "PhysicalObject.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"
#include <limits>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Physics Demo", 640, 480);

	PhysicalObject ground(Rectangle(Vector2D(0, -14), Vector2D(20, 1)), std::numeric_limits<float>::infinity());
	PhysicalObject rect(Rectangle(Vector2D(0, 0), Vector2D(2,3), 1), 1);

	ground.SetRestitutionCoefficient(1);
	rect.SetRestitutionCoefficient(1);

	Painter p;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		rect.SetVelocity(rect.GetVelocity() + Vector2D(0,-3)*PhysicalObject::GetDeltaTime());

		p.PaintRectangle(ground.GetColliderAsRectangle());
		p.PaintRectangle(rect.GetColliderAsRectangle());

		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}