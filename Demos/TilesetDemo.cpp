#include "GameManager.hpp"
#include "Tileset.hpp"
#include "Sprite.hpp"
#include "Vector2D.hpp"

#include <iostream>

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Tileset Demo", 640, 480);

	Tileset tileset(TIN_DEMO_LOCATION "Sprites/spr_tileset_foreground.png", 8, 8);

	std::cout << "Rows: " << tileset.GetRowCount() << std::endl;
	std::cout << "Columns: " << tileset.GetColumnCount() << std::endl;

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		for (uint16_t i = 0; i < tileset.GetRowCount(); i++) {
			for (uint16_t j = 0; j < tileset.GetColumnCount(); j++) {
				std::cout << "Id: " << i*tileset.GetColumnCount() + j << std::endl;
				tileset.GetTile(i*tileset.GetColumnCount() + j).Draw(0.5*Vector2D(j,-i));
			}
		}
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}