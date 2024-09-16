#include "Animation.hpp"
#include "FunctionalObject.hpp"
#include "GameManager.hpp"
#include "KeyboardManager.hpp"
#include "Painter.hpp"
#include "PhysicalObject.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"
#include "VisualObject.hpp"
#include <cmath>
#include <limits>

#include "Painter.hpp"
#include <iostream>

using namespace Tin;

class Player : public FunctionalObject, public PhysicalObject, public VisualObject {
	public:
	Player() : PhysicalObject(Rectangle(Vector2D(0,7.0/4),Vector2D(3.0/4,7.0/4)),1), VisualObject(Vector2D(0,0),1) {
		if (animIdle == nullptr || animWalk == nullptr) {
			animIdle = new Animation(TIN_DEMO_LOCATION "Sprites/spr_player_default-Sheet.png", 24, 56, 45, Vector2D(3.0/4, 0));
			animWalk = new Animation(TIN_DEMO_LOCATION "Sprites/spr_player_walk-Sheet.png", 26, 56, 10, Vector2D(3.0/4, 0));
		}

		this->SetVisual(*animIdle);
		this->SetLockRotation(true);
	}

	virtual void OnUpdate() override {
		this->SetVelocity(this->GetVelocity() + Vector2D(0,-5)*PhysicalObject::GetDeltaTime());

		Painter p;
		p.PaintRectangle(this->GetColliderAsRectangle());

		KeyboardManager* keyboardManager = KeyboardManager::GetCurrentManager();

		int direction = keyboardManager->KeyDown("right") - keyboardManager->KeyDown("left");

		if (fabs(this->GetVelocity().x + this->acceleration*direction*GetDeltaTime()) <= this->maxSpeed) {
			this->SetVelocity(this->GetVelocity() + Vector2D(this->acceleration*direction*GetDeltaTime(),0));
		}
		if (direction == 0) {
			float sign = (this->GetVelocity().x == 0) ? 0 : this->GetVelocity().x/fabs(this->GetVelocity().x);
			this->SetVelocity(this->GetVelocity() - sign*Vector2D(decceleration*GetDeltaTime(),0));

			if (fabs(this->GetVelocity().x) <= decceleration*GetDeltaTime()) {
				this->SetVelocity(Vector2D(0, this->GetVelocity().y));
			}
		}

		if (direction != 0) this->SetFlip(direction < 0, false);
		if (direction != 0) this->SetVisual(*animWalk);
		else this->SetVisual(*animIdle);
	}

	private:
	float maxSpeed = 7.5;
	float acceleration = 20;
	float decceleration = 20;

	static Animation* animIdle;
	static Animation* animWalk;
};

Animation* Player::animIdle = nullptr;
Animation* Player::animWalk = nullptr;


int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("FPV Demo", 640, 480);

	Player player;

	PhysicalObject ground(Rectangle(Vector2D(0, -16), Vector2D(20, 1)), std::numeric_limits<float>::infinity());
	PhysicalObject ceiling(Rectangle(Vector2D(0, 16), Vector2D(20, 1)), std::numeric_limits<float>::infinity());
	PhysicalObject wallRight(Rectangle(Vector2D(21, 0), Vector2D(1, 15)), std::numeric_limits<float>::infinity());
	PhysicalObject wallLeft(Rectangle(Vector2D(-21, 0), Vector2D(1, 15)), std::numeric_limits<float>::infinity());

	ground.SetRestitutionCoefficient(0);
	ceiling.SetRestitutionCoefficient(0);
	wallRight.SetRestitutionCoefficient(0);
	wallLeft.SetRestitutionCoefficient(0);

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}