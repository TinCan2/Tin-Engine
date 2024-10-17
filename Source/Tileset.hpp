#pragma once
#include <cstdint>
#include <memory>

namespace Tin {
	struct Sprite;

	class Tileset {
		public:
		Tileset(const char* targetSheet, const uint16_t& w, const uint16_t& h);

		Tileset(const Tileset& coppiedTileset);
		Tileset& operator=(const Tileset& coppiedTileset);

		~Tileset();

		uint16_t GetRowCount() const;
		uint16_t GetColumnCount() const;

		Sprite GetTile(uint16_t tileId);

		private:
		std::shared_ptr<Sprite>* tiles;
		uint16_t rows, columns;

	};
}