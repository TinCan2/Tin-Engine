#include "Sprite.hpp"
#include "Tileset.hpp"
#include <stdexcept>

#include <iostream>

using namespace Tin;

//Construction and Destruction
Tileset::Tileset(const char* targetSheet, const uint16_t& w, const uint16_t& h, const uint16_t& margin) {
	Sprite sheet(targetSheet);

    this->columns = sheet.GetWidth()/(w+2*margin);
	this->rows = sheet.GetHeight()/(h+2*margin);

//	std::cout << (sheet.GetWidth()) << std::endl;
//	std::cout << (w+xM) << std::endl;
//
//	std::cout << "X Margin: " << xM << std::endl;
//	std::cout << "Y Margin: " << yM << std::endl;

	this->tiles = new std::shared_ptr<Sprite>[this->columns*this->rows];
	for (size_t i = 0; i < this->rows; i++){
		for (size_t j = 0; j < this->columns; j++) {
			uint16_t x = margin + j*(w+2*margin);
			uint16_t y = (this->rows-i-1)*(h+2*margin)+margin;
			this->tiles[i*this->columns+j] = std::make_shared<Sprite>(targetSheet, x, y, w, h);
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
Sprite& Tileset::GetTile(uint16_t tileId) {
	if (tileId >= this->columns*this->rows) throw std::runtime_error("Tile out of bounds.");
	return *this->tiles[tileId];
}

uint16_t Tileset::GetRowCount() const {
	return this->rows;
}

uint16_t Tileset::GetColumnCount() const {
	return this->columns;
}