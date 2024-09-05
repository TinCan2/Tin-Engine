#include "Circle.hpp"
#include "Color.hpp"
#include "GameManager.hpp"
#include "MouseManager.hpp"
#include "Painter.hpp"
#include "Vector2D.hpp"
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Input Demo", 640, 480);

	MouseManager* mouseManager = MouseManager::GetCurrentInstance();

	Painter p;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();

		p.SetPaintColor(Color(255,255,255));
		for (int i = -10; i <= 10; i++) {
			p.PaintLine(Vector2D(i,-10), Vector2D(i, 10));
			p.PaintLine(Vector2D(-10,i), Vector2D(10, i));
		}

		p.SetPaintColor(Color(255,0,0));
		p.PaintCircle(Circle(Vector2D(0,0),0.5f));

		Vector2D mousePos = mouseManager->GetMousePosition();
		std::cout << "Mouse position: " << mousePos.x << ";" << mousePos.y << std::endl;

		std::cout << "Current button: ";
		switch (mouseManager->GetLastButton()) {
			case MouseManager::Buttons::Left:
				std::cout << "Left" << std::endl;
				break;
			case MouseManager::Buttons::Middle:
				std::cout << "Middle" << std::endl;
				break;
			case MouseManager::Buttons::Right:
				std::cout << "Right" << std::endl;
				break;
			case MouseManager::Buttons::SideBack:
				std::cout << "SideBack" << std::endl;
				break;
			case MouseManager::Buttons::SideFront:
				std::cout << "SideFront" << std::endl;
				break;
			case MouseManager::Buttons::None:
				std::cout << "None" << std::endl;
				break;
		}
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}