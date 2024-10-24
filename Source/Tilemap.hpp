#pragma once
#include "VisualObject.hpp"
#include <cstdint>
#include <memory>

namespace Tin {
	struct Tileset;
	struct Vector2D;

	typedef const size_t csize_t;
	typedef const Vector2D cVec2;
	typedef const float cfloat;

	class Tilemap : public VisualObject {
		public:
		Tilemap(Tileset* const& sets, csize_t& sC, csize_t& w, csize_t& h, size_t** const& idM, cVec2& tS, cVec2& anc, cfloat& d);

		Tilemap(const Tilemap& coppiedTilemap);
		Tilemap& operator=(const Tilemap& coppiedTilemap);

		virtual ~Tilemap();

		virtual void OnRender() override;

		private:
		std::shared_ptr<Tileset>* tilesets;
		size_t setCount;
        size_t* setBounds;

		size_t** idMatrix;
		size_t w,h;

		Vector2D* anchor;
		Vector2D* tileSize;
	};
}