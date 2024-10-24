#include "GameManager.hpp"
#include "Painter.hpp"
#include "PhysicalObject.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"
#include <limits>

using namespace Tin;

class Barrier : public PhysicalObject {
	public:
	Barrier(const Rectangle& bounds) : PhysicalObject(bounds, std::numeric_limits<float>::infinity()) {
		this->SetRestitutionCoefficient(1);
	}

	virtual void OnCollision(Vector2D contact, Vector2D normal) override {}
};

class Ball : public PhysicalObject {
	public:
	Ball(const Rectangle& bounds) : PhysicalObject(bounds, 1) {
		this->SetRestitutionCoefficient(0.25);
	}

	virtual void OnCollision(Vector2D contact, Vector2D normal) override {}
};

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Physics Demo", 640, 480);

	Barrier ground(Rectangle(Vector2D(0, -16), Vector2D(20, 1)));
	Barrier ceiling(Rectangle(Vector2D(0, 16), Vector2D(20, 1)));
	Barrier wallRight(Rectangle(Vector2D(21, 0), Vector2D(1, 15)));
	Barrier wallLeft(Rectangle(Vector2D(-21, 0), Vector2D(1, 15)));

	Ball rect(Rectangle(Vector2D(0, 0), Vector2D(2,3), 1));

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