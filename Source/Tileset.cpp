#include "Sprite.hpp"
#include "Tileset.hpp"

#include <stdexcept>

using namespace Tin;

//Construction and Destruction
Tileset::Tileset(const char* targetSheet, const uint16_t& w, const uint16_t& h) {
	Sprite sheet(targetSheet);

    this->columns = sheet.GetWidth()/w;
	this->rows = sheet.GetHeight()/h;

	this->tiles = new std::shared_ptr<Sprite>[this->columns*this->rows];
	for (size_t i = 0; i < this->rows; i++){
		for (size_t j = 0; j < this->columns; j++) {
			this->tiles[i*this->columns+j] = std::make_shared<Sprite>(targetSheet, j*w, (this->rows-i-1)*h, w, h);
		}
	}

}

Tileset::Tileset(const Tileset& coppiedTileset) {
	this->columns = coppiedTileset.columns;
	this->rows = coppiedTileset.rows;

	this->tiles = new std::shared_ptr<Sprite>[this->columns*this->rows];
	for (size_t i = 0; i < this->columns*this->rows; i++) this->tiles[i] = coppiedTileset.tiles[i];
}

Tileset& Tileset::operator=(const Tileset& coppiedTileset) {
	delete[] this->tiles;

	this->columns = coppiedTileset.columns;
	this->rows = coppiedTileset.rows;

	this->tiles = new std::shared_ptr<Sprite>[this->columns*this->rows];
	for (size_t i = 0; i < this->columns*this->rows; i++) this->tiles[i] = coppiedTileset.tiles[i];

	return *this;
}

Tileset::~Tileset() {
	delete[] this->tiles;
}


//Member Access
Sprite Tileset::GetTile(uint16_t tileId) {
	if (tileId >= this->columns*this->rows) throw std::runtime_error("Tile out of bounds.");
	return *this->tiles[tileId];
}

uint16_t Tileset::GetRowCount() const {
	return this->rows;
}

uint16_t Tileset::GetColumnCount() const {
	return this->columns;
}