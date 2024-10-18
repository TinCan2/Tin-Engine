#pragma once
#include "ModuleDefinitions.hpp"
#include "VisualObject.hpp"
#include <memory>

namespace Tin {
	struct Tileset;
	struct Vector2D;

	class PhysicalObject;

	class Tilemap : public VisualObject {
		public:
		Tilemap(Tileset* const& sets, const uint16_t& tilesetCount, const uint16_t& w, const uint16_t& h, const Vector2D& tileSize, const Vector2D& anchor, const float& depth);

		Tilemap(const Tilemap& coppiedTilemap);
		Tilemap& operator=(const Tilemap& coppiedTilemap);

		virtual ~Tilemap();

		virtual void OnRender() override;

		void SetTileID(size_t x, size_t y, size_t id);
		size_t GetTileID(size_t x, size_t y) const;

		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			void GeneratePhysics();
		#endif

		private:
		std::shared_ptr<Tileset>* tilesets;
		size_t setCount;
		size_t* setBounds;

		size_t** tileMatrix;
		size_t w,h;

		#ifdef TIN_MODULES_INCLUDE_PHYSICS
			PhysicalObject* physics;
		#endif

		Vector2D* anchor;
		Vector2D* tileSize;
	};
}