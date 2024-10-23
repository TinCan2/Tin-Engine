#pragma once
#include "DllMacro.hpp"
#include <cstddef>
#include <cstdint>
#include <map>

struct SDL_Renderer;
struct SDL_Texture;

namespace Tin {

	struct Vector2D;

	typedef const uint16_t cuint16_t;

	class TIN_API Sprite {
		public:
		Sprite(const char* targetFile);
		Sprite(const char* targetFile, const Vector2D& origin);
		Sprite(const char* targetFile, cuint16_t& x, cuint16_t& y, cuint16_t& w, cuint16_t& h);
		Sprite(const char* targetFile, cuint16_t& x, cuint16_t& y, cuint16_t& w, cuint16_t& h, const Vector2D& origin);

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

		static void GenerateTexture(const char* targetFile);

		static SDL_Renderer* boundedRenderer;
		friend class GameManager;

		struct Texture{SDL_Texture* SDLTexture; size_t refCount;};
		static std::map<const char*, Texture> textureMap;
	};
}