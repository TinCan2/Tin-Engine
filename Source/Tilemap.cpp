#include "Sprite.hpp"
#include "Tilemap.hpp"
#include "Tileset.hpp"
#include "Vector2D.hpp"
#include <cstring>

#include <iostream>

using namespace Tin;

//Construction and Destruction
Tilemap::Tilemap(Tileset* const& sets, const uint16_t& tilesetCount, const uint16_t& w, const uint16_t& h, const Vector2D& tileSize, const Vector2D& anchor, const float& depth):
VisualObject(anchor, depth) {
	this->tilesets = new std::shared_ptr<Tileset>[tilesetCount];
	this->setCount = tilesetCount;
	this->setBounds = new size_t[tilesetCount];

	for (int i = 0; i < tilesetCount; i++) {
		this->tilesets[i] = std::make_shared<Tileset>(sets[i]);
		if (i == 0) this->setBounds[i] = sets[i].GetRowCount()*sets[i].GetColumnCount();
		else this->setBounds[i] = sets[i].GetRowCount()*sets[i].GetColumnCount() + this->setBounds[i-1];
	}

	this->tileMatrix = new size_t*[h];
	for (int i = 0; i < h; i++) {
		this->tileMatrix[i] = new size_t[w];
		for (int j = 0; j < w; j++) this->tileMatrix[i][j] = 0;
	}

	this->w = w;
	this->h = h;

	this->anchor = new Vector2D(anchor);
	this->tileSize = new Vector2D(tileSize);
}

Tilemap::Tilemap(const Tilemap& coppiedTilemap) :
VisualObject(coppiedTilemap) {
	this->tilesets = new std::shared_ptr<Tileset>[coppiedTilemap.setCount];
	this->setCount = coppiedTilemap.setCount;
	this->setBounds = new size_t[coppiedTilemap.setCount];

	for (int i = 0; i < coppiedTilemap.setCount; i++) this->tilesets[i] = coppiedTilemap.tilesets[i];
	std::memcpy(this->setBounds, coppiedTilemap.setBounds, sizeof(size_t)*coppiedTilemap.setCount);

	this->tileMatrix = new size_t*[coppiedTilemap.h];
	for (int i = 0; i < coppiedTilemap.h; i++) {
		this->tileMatrix[i] = new size_t[coppiedTilemap.w];
		for (int j = 0; j < w; j++) this->tileMatrix[i][j] = 0;
	}

	this->w = coppiedTilemap.w;
	this->h = coppiedTilemap.h;

	this->anchor = new Vector2D(*coppiedTilemap.anchor);
	this->tileSize = new Vector2D(*coppiedTilemap.tileSize);
}


Tilemap& Tilemap::operator=(const Tilemap& coppiedTilemap) {
	delete[] this->tilesets;
	delete[] this->setBounds;

	for (size_t i = 0; i < h; i++) delete[] this->tileMatrix[i];
	delete[] this->tileMatrix;

	*static_cast<VisualObject*>(this) = static_cast<VisualObject>(coppiedTilemap);

	this->tilesets = new std::shared_ptr<Tileset>[coppiedTilemap.setCount];
	this->setCount = coppiedTilemap.setCount;
	this->setBounds = new size_t[coppiedTilemap.setCount];

	for (int i = 0; i < coppiedTilemap.setCount; i++) this->tilesets[i] = coppiedTilemap.tilesets[i];
	std::memcpy(this->setBounds, coppiedTilemap.setBounds, sizeof(size_t)*coppiedTilemap.setCount);

	this->tileMatrix = new size_t*[coppiedTilemap.h];
	for (int i = 0; i < coppiedTilemap.h; i++) {
		this->tileMatrix[i] = new size_t[coppiedTilemap.w];
		for (int j = 0; j < w; j++) this->tileMatrix[i][j] = 0;
	}

	this->w = coppiedTilemap.w;
	this->h = coppiedTilemap.h;

	*this->anchor = *coppiedTilemap.anchor;
	*this->tileSize = *coppiedTilemap.tileSize;

	return *this;
}

Tilemap::~Tilemap() {
	delete[] this->tilesets;
	delete[] this->setBounds;

	for (size_t i = 0; i < h; i++) delete[] this->tileMatrix[i];
	delete[] this->tileMatrix;

	delete this->anchor;
	delete this->tileSize;
}


void Tilemap::OnRender() {
	for (size_t i = 0; i < this->h; i++) {
		for (size_t j = 0; j < this->w; j++) {
			size_t tileID = this->tileMatrix[i][j];
			if (tileID == 0) continue;
			std::cout << "TileID: " << tileID << std::endl;

			size_t setID = 0;
			while (tileID > this->setBounds[setID]) setID++;

			if (setID > 0) tileID -= this->setBounds[setID-1];
			tileID--;
			std::cout << "Transformed TileID: " << tileID << std::endl;

			Vector2D offset(j*this->tileSize->x, i*this->tileSize->y);
			this->tilesets[setID]->GetTile(tileID).Draw(*this->anchor + offset);
		}
	}
}

void Tilemap::SetTileID(size_t x, size_t y, size_t id) {
	this->tileMatrix[y][x] = id;
}