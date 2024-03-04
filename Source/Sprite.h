#pragma once
#include <map>

typedef unsigned int UInt16;

struct Vector2D;
struct SDL_Renderer;
struct SDL_Texture;

class Sprite {
	public:
	Sprite(const char* targetFile);
	Sprite(const char* targetFile, const Vector2D& origin);
	Sprite(const char* targetFile, UInt16 x, UInt16 y, UInt16 w, UInt16 h);
	Sprite(const char* targetFile, UInt16 x, UInt16 y, UInt16 w, UInt16 h, const Vector2D& origin);

	Sprite(const Sprite& coppiedSprite);

	~Sprite();

	void Draw(const Vector2D& position);
	void Draw(const Vector2D& position, bool flipH, bool flipV);
	void Draw(const Vector2D& position, float rotation);
	void Draw(const Vector2D& position, bool flipH, bool flipV, float rotation);

	UInt16 GetWidth();
	UInt16 GetHeight();

	private:
	const char* boundTexture;

	UInt16 x, y, w ,h;

	Vector2D* origin;

	friend void GenerateTexture(const char* targetFile);
	friend class GameManager;

	static SDL_Renderer* boundedRenderer;
	static std::map<const char*, std::pair<SDL_Texture*, UInt16>*> textureMap;
};