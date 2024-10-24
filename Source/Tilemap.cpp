#include "JointShape.hpp"
#include "PhysicalObject.hpp"
#include "Rectangle.hpp"
#include "Tilemap.hpp"
#include "Tileset.hpp"
#include "Vector2D.hpp"
#include <cstring>
#include <limits>
#include <vector>

using namespace Tin;

//Construction and Destruction
#ifdef TIN_MODULES_INCLUDE_PHYSICS
	Tilemap::Tilemap(Tileset* const& sets, csize_t& sC, csize_t& w, csize_t& h, size_t** const& idM, cVec2& tS, cVec2& anc, cfloat& d, const bool& solid) :
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

		if (solid) {
			bool** coverMatrix = new bool*[this->h];
			for (int i = 0; i < h; i++) {
				coverMatrix[i] = new bool[w];
				for (int j = 0; j < w; j++) coverMatrix[i][j] = false;
			}

			std::vector<Rectangle> coverList;
			for (size_t i = 0; i < this->h; i++) {
				for (size_t j = 0; j < this->w; j++) {
					if (coverMatrix[i][j]) continue;

					size_t tileID = this->idMatrix[i][j];
					size_t lim = this->setBounds[this->setCount-1];
					if (tileID < lim) {
						size_t maxX=j;
						while (this->idMatrix[i][maxX] < lim && !coverMatrix[i][maxX] && maxX < this->w) {
							maxX++;
						}
						maxX -= 1;

						size_t maxY = this->h-1;
						for (size_t x = j; x <= maxX; x++) {
							for (size_t y = i; y <= maxY; y++) {
								if (this->idMatrix[y][x] >= lim || coverMatrix[y][x]) maxY = y-1;
							}
						}

						Vector2D a(j*this->tileSize->x, i*this->tileSize->y);
						Vector2D b((maxX+1)*this->tileSize->x, (maxY+1)*this->tileSize->y);
						a+=*this->anchor;
						b+=*this->anchor;
						coverList.push_back(Rectangle((a+b)/2, (b-a)/2));

						for (size_t x = j; x <= maxX; x++) {
							for(size_t y = i; y <= maxY; y++) coverMatrix[y][x] = true;
						}
					}
				}
			}

			for (int i = 0; i < h; i++) delete[] coverMatrix[i];
			delete[] coverMatrix;

			JointShape colliderShape(nullptr, 0, &coverList[0], coverList.size(), *this->anchor);
			this->collider = new PhysicalObject(colliderShape, std::numeric_limits<float>::infinity());
		}
		else this->collider = nullptr;
	}
#else
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
#endif

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

	#ifdef TIN_MODULES_INCLUDE_PHYSICS
		if (coppiedTilemap.collider != nullptr) this->collider = new PhysicalObject(*coppiedTilemap.collider);
	#endif
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

	#ifdef TIN_MODULES_INCLUDE_PHYSICS
		if (coppiedTilemap.collider != nullptr) *this->collider = *coppiedTilemap.collider;
		else if (this->collider != nullptr) delete this->collider;
	#endif

	return *this;
}

Tilemap::~Tilemap() {
	delete[] this->tilesets;
	delete[] this->setBounds;

	for (size_t i = 0; i < h; i++) delete[] this->idMatrix[i];
	delete[] this->idMatrix;

	delete this->anchor;
	delete this->tileSize;

	#ifdef TIN_MODULES_INCLUDE_PHYSICS
		if (this->collider != nullptr) delete this->collider;
	#endif
}


//Renderer Access
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