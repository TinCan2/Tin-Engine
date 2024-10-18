#include "Animation.hpp"
#include "FunctionalObject.hpp"
#include "GameManager.hpp"
#include "KeyboardManager.hpp"
#include "Painter.hpp"
#include "PhysicalObject.hpp"
#include "Rectangle.hpp"
#include "Sprite.hpp"
#include "Tilemap.hpp"
#include "Tileset.hpp"
#include "Vector2D.hpp"
#include "VisualObject.hpp"
#include <cmath>
#include <limits>

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

	gameManager->Initialize("Tilemap Demo", 640, 480);

	Tileset sets[] = {Tileset(TIN_DEMO_LOCATION "Sprites/spr_tileset_grass.png", 16, 16),
					  Tileset(TIN_DEMO_LOCATION "Sprites/spr_tileset_rock.png", 16, 16)};

	Tilemap map(sets, 2, 40, 30, Vector2D(1,1), Vector2D(-20,-15), 0);

	size_t ids[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					35,17,12,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					93,31,15,24,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,93,31,15,24,12,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,102,93,31,32,15,24,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,102,102,92,93,31,32,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,102,102,102,102,109,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,102,102,102,103,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,102,102,102,103,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,102,102,102,104,93,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					102,102,102,102,102,103,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,12,12,
					102,102,102,102,102,103,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,25,22,22,
					102,102,102,102,94,113,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,22,22,
					102,102,102,94,113,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,25,22,22,22,
					102,94,112,113,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,25,22,22,22,22,
					112,113,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,25,22,22,22,22,22,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,22,22,22,22,22,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,25,22,22,22,22,22,22,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,22,22,22,22,22,22,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,25,22,22,22,22,22,22,22,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,13,0,0,0,0,0,11,25,22,22,22,22,22,22,22,22,
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,12,12,25,24,13,0,0,0,11,25,22,22,22,22,22,22,22,22,22,
					92,92,93,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,12,25,22,22,22,22,24,12,12,12,25,22,22,22,22,22,22,22,22,22,22,
					102,102,104,92,92,93,0,0,0,91,92,93,0,0,0,0,16,17,25,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
					102,102,102,102,102,104,92,92,92,105,94,113,0,0,0,0,0,31,15,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
					102,102,102,102,102,102,102,102,102,102,103,0,0,0,0,0,0,0,31,32,15,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
					102,102,102,102,102,102,102,102,102,102,103,0,0,0,0,0,0,0,0,0,21,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22};

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 40; j++) map.SetTileID(j, i, ids[(29-i)*40+j]);
	}

	map.GeneratePhysics();

	Player p;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}