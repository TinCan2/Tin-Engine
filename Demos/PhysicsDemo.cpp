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

	PhysicalObject ground(Rectangle(Vector2D(0, -16), Vector2D(20, 1)), std::numeric_limits<float>::infinity());
	PhysicalObject ceiling(Rectangle(Vector2D(0, 16), Vector2D(20, 1)), std::numeric_limits<float>::infinity());
	PhysicalObject wallRight(Rectangle(Vector2D(21, 0), Vector2D(1, 15)), std::numeric_limits<float>::infinity());
	PhysicalObject wallLeft(Rectangle(Vector2D(-21, 0), Vector2D(1, 15)), std::numeric_limits<float>::infinity());


	PhysicalObject rectA(Rectangle(Vector2D(0, 0), Vector2D(2,3), 1), 1);
	PhysicalObject rectB(Rectangle(Vector2D(1, 8), Vector2D(2,3), -1), 1);

	ground.SetRestitutionCoefficient(1);
	ceiling.SetRestitutionCoefficient(1);
	wallRight.SetRestitutionCoefficient(1);
	wallLeft.SetRestitutionCoefficient(1);


	rectA.SetRestitutionCoefficient(1);
	rectB.SetRestitutionCoefficient(1);

//	rectA.SetLockRotation(true);

	Painter p;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		rectA.SetVelocity(rectA.GetVelocity() + Vector2D(0,-3)*PhysicalObject::GetDeltaTime());
		rectB.SetVelocity(rectB.GetVelocity() + Vector2D(0,-3)*PhysicalObject::GetDeltaTime());

		p.PaintRectangle(rectA.GetColliderAsRectangle());
		p.PaintRectangle(rectB.GetColliderAsRectangle());

		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}