#include "GameManager.hpp"
#include "Tilemap.hpp"
#include "Tileset.hpp"
#include "Vector2D.hpp"
#include "Sprite.hpp"

#include <iostream>

using namespace Tin;

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
//		for (int j = 0; j < 40; j++) std::cout << ids[1199-(i*30+j)] << std::endl;
	}

//	map.SetTileID(0,0,41);

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}