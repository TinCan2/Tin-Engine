#pragma once
#include <cstdint>
#include <memory>

namespace Tin {
	struct Vector2D;
	class Sprite;

	class TIN_API Tileset {
		public:
		Tileset(const char* targetSheet, const uint16_t& w, const uint16_t& h);

		Tileset(const Tileset& coppiedTileset);
		Tileset& operator=(const Tileset& coppiedTileset);

		~Tileset();

		uint16_t GetRowCount() const;
		uint16_t GetColumnCount() const;

		void DrawTile(const size_t& Id, const Vector2D& pos);

		private:
		std::shared_ptr<Sprite>* tiles;
		uint16_t rows, columns;
	};
}