#include "Sprite.hpp"
#include "Tilemap.hpp"
#include "Tileset.hpp"
#include "Vector2D.hpp"
#include <cstring>

using namespace Tin;

//Construction and Destruction
Tilemap::Tilemap(Tileset* const& sets, csize_t& sC, csize_t& w, csize_t& h, size_t** const& idM, cVec2& tS, cVec2& anc, cfloat& d) :
VisualObject(anc, d) {
	this->tilesets = new std::shared_ptr<Tileset>[sC];
	this->setCount = sC;
	this->setBounds = new size_t[sC];

	for (int i = 0; i < setCount; i++) {
		this->tilesets[i] = std::make_shared<Tileset>(sets[i]);
		if (i == 0) this->setBounds[i] = sets[i].GetRowCount()*sets[i].GetColumnCount();
		else this->setBounds[i] = sets[i].GetRowCount()*sets[i].GetColumnCount() + this->setBounds[i-1];
	}

	this->idMatrix = new size_t*[h];
	for (int i = 0; i < h; i++) {
		this->idMatrix[i] = new size_t[w];
		for (int j = 0; j < w; j++) this->idMatrix[i][j] = idM[i][j];
	}

	this->w = w;
	this->h = h;

	this->anchor = new Vector2D(anc);
	this->tileSize = new Vector2D(tS);
}

Tilemap::Tilemap(const Tilemap& coppiedTilemap) :
VisualObject(coppiedTilemap) {
	this->tilesets = new std::shared_ptr<Tileset>[coppiedTilemap.setCount];
	this->setCount = coppiedTilemap.setCount;
	this->setBounds = new size_t[coppiedTilemap.setCount];

	for (int i = 0; i < coppiedTilemap.setCount; i++) this->tilesets[i] = coppiedTilemap.tilesets[i];
	std::memcpy(this->setBounds, coppiedTilemap.setBounds, sizeof(size_t)*coppiedTilemap.setCount);

	this->idMatrix = new size_t*[coppiedTilemap.h];
	for (int i = 0; i < coppiedTilemap.h; i++) {
		this->idMatrix[i] = new size_t[coppiedTilemap.w];
		for (int j = 0; j < w; j++) this->idMatrix[i][j] = coppiedTilemap.idMatrix[i][j];
	}

	this->w = coppiedTilemap.w;
	this->h = coppiedTilemap.h;

	this->anchor = new Vector2D(*coppiedTilemap.anchor);
	this->tileSize = new Vector2D(*coppiedTilemap.tileSize);
}


Tilemap& Tilemap::operator=(const Tilemap& coppiedTilemap) {
	delete[] this->tilesets;
	delete[] this->setBounds;

	for (size_t i = 0; i < h; i++) delete[] this->idMatrix[i];
	delete[] this->idMatrix;

	*static_cast<VisualObject*>(this) = static_cast<VisualObject>(coppiedTilemap);

	this->tilesets = new std::shared_ptr<Tileset>[coppiedTilemap.setCount];
	this->setCount = coppiedTilemap.setCount;
	this->setBounds = new size_t[coppiedTilemap.setCount];

	for (int i = 0; i < coppiedTilemap.setCount; i++) this->tilesets[i] = coppiedTilemap.tilesets[i];
	std::memcpy(this->setBounds, coppiedTilemap.setBounds, sizeof(size_t)*coppiedTilemap.setCount);

	this->idMatrix = new size_t*[coppiedTilemap.h];
	for (int i = 0; i < coppiedTilemap.h; i++) {
		this->idMatrix[i] = new size_t[coppiedTilemap.w];
		for (int j = 0; j < w; j++) this->idMatrix[i][j] = coppiedTilemap.idMatrix[i][j];
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

	for (size_t i = 0; i < h; i++) delete[] this->idMatrix[i];
	delete[] this->idMatrix;

	delete this->anchor;
	delete this->tileSize;
}


void Tilemap::OnRender() {
	for (size_t i = 0; i < this->h; i++) {
		for (size_t j = 0; j < this->w; j++) {
			size_t tileID = this->idMatrix[i][j];
			if (tileID == -1) continue;

			size_t setID = 0;
			while (tileID > this->setBounds[setID]) setID++;

			size_t ttID = (setID > 0) ? tileID - this->setBounds[setID-1] : tileID;
			Vector2D offset(j*this->tileSize->x, i*this->tileSize->y);
			this->tilesets[setID]->DrawTile(ttID,*this->anchor + offset);
		}
	}
}