#include "FunctionalObject.hpp"
#include "GameManager.hpp"
#include "Painter.hpp"
#include "PhysicalObject.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"
#include <limits>

using namespace Tin;

class Ball : public PhysicalObject , public FunctionalObject {
	public:
	Ball(const Rectangle& bounds) : PhysicalObject(bounds, 1) {
		this->SetRestitutionCoefficient(1);
	}

	virtual void OnUpdate() override {
		this->SetVelocity(this->GetVelocity() + Vector2D(0,-3)*PhysicalObject::GetDeltaTime());
	}
};

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Physics Demo", 640, 480);

	PhysicalObject ground(Rectangle(Vector2D(0, -16), Vector2D(20, 1)), std::numeric_limits<float>::infinity());
	PhysicalObject ceiling(Rectangle(Vector2D(0, 16), Vector2D(20, 1)), std::numeric_limits<float>::infinity());
	PhysicalObject wallRight(Rectangle(Vector2D(21, 0), Vector2D(1, 15)), std::numeric_limits<float>::infinity());
	PhysicalObject wallLeft(Rectangle(Vector2D(-21, 0), Vector2D(1, 15)), std::numeric_limits<float>::infinity());

	Ball rect(Rectangle(Vector2D(0, 0), Vector2D(2,3), 1));

	Painter p;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();

		p.PaintRectangle(rect.GetColliderAsRectangle());

		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}