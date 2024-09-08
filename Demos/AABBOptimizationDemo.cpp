#include "Circle.hpp"
#include "CollisionInfo.hpp"
#include "Color.hpp"
#include "GameManager.hpp"
#include "Painter.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"

#include <cmath>
#include <iostream>


using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("AABB Optimziation Demo", 640, 480);

	Rectangle rectA(Vector2D(-3,0), Vector2D(1,2), 7.23+4*M_PI/2); //Orange
	Rectangle rectB(Vector2D(-4,2), Vector2D(1,2), 7.23); //Blue

	Painter p;

	CollisionInfo ci;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();

		p.SetPaintColor(Color(255,255,0));
		p.PaintRectangle(rectA);
		p.SetPaintColor(Color(0,255,255));
		p.PaintRectangle(rectB);

		std::cout << "Collision result: " << rectA.CollidesWith(rectB, &ci) << std::endl;

		p.SetPaintColor(Color(255,255,255));
		p.PaintCircle(Circle(ci.GetContact(),0.25f));
		p.PaintLine(ci.GetContact(), ci.GetContact() + ci.GetNormal());

		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}