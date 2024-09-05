#pragma once
#include "DllMacro.hpp"
#include <map>

struct SDL_Renderer;
struct SDL_Texture;

namespace Tin {

	struct Vector2D;

	class TIN_API Sprite {
		public:
		Sprite(const char* file);
		Sprite(const char* file, const Vector2D& origin);
		Sprite(const char* file, const uint16_t& x, const uint16_t& y, const uint16_t& w, const uint16_t& h);
		Sprite(const char* file, const uint16_t& x, const uint16_t& y, const uint16_t& w, const uint16_t& h, const Vector2D& origin);

		Sprite(const Sprite& coppiedSprite);
		Sprite& operator=(const Sprite& coppiedSprite);

		~Sprite();

		void Draw(const Vector2D& position, const bool& flipH=false, const bool& flipV=false, const float& rotation = 0) const;

		uint16_t GetWidth() const;
		uint16_t GetHeight() const;

		private:
		const char* boundTexture;

		uint16_t x, y, w ,h;

		Vector2D* origin;

		static void GenerateTexture(const char* file);

		friend class GameManager;

		static SDL_Renderer* boundedRenderer;
		static std::map<const char*, std::pair<SDL_Texture*, uint16_t>*> textureMap;
	};
}