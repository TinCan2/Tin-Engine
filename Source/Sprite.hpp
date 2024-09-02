#pragma once
#include "DllMacro.hpp"
#include <map>

struct SDL_Renderer;
struct SDL_Texture;

namespace Tin {
	typedef unsigned int UInt16;

	struct Vector2D;

	class TIN_API Sprite {
		public:
		Sprite(const char* targetFile);
		Sprite(const char* targetFile, const Vector2D& origin);
		Sprite(const char* targetFile, const UInt16& x, const UInt16& y, const UInt16& w, const UInt16& h);
		Sprite(const char* targetFile, const UInt16& x, const UInt16& y, const UInt16& w, const UInt16& h, const Vector2D& origin);

		Sprite(const Sprite& coppiedSprite);
		Sprite& operator=(const Sprite& coppiedSprite);

		~Sprite();

		void Draw(const Vector2D& position, const bool& flipH=false, const bool& flipV=false, const float& rotation = 0) const;

		UInt16 GetWidth() const;
		UInt16 GetHeight() const;

		private:
		const char* boundTexture;

		UInt16 x, y, w ,h;

		Vector2D* origin;

		static void GenerateTexture(const char* targetFile);

		friend class GameManager;

		static SDL_Renderer* boundedRenderer;
		static std::map<const char*, std::pair<SDL_Texture*, UInt16>*> textureMap;
	};
}