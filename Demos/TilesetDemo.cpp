#include "Circle.hpp"
#include "Color.hpp"
#include "GameManager.hpp"
#include "Painter.hpp"
#include "Sprite.hpp"
#include "Tileset.hpp"
#include "Vector2D.hpp"
#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Tileset Demo", 640, 480);

	Tileset tileset(TIN_DEMO_LOCATION "Sprites/spr_tileset_foreground -padded.png", 8, 8, 1);

	std::cout << "Rows: " << tileset.GetRowCount() << std::endl;
	std::cout << "Columns: " << tileset.GetColumnCount() << std::endl;

	Painter p(Color(255,0,0));

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		for (uint16_t i = 0; i < tileset.GetRowCount(); i++) {
			for (uint16_t j = 0; j < tileset.GetColumnCount(); j++) {
				std::cout << "Id: " << i*tileset.GetColumnCount() + j << std::endl;
				tileset.DrawTile(i*tileset.GetColumnCount() + j, 0.5*Vector2D(j,-i));
			}
		}
		p.PaintCircle(Circle(Vector2D(0,0),0.25));
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}