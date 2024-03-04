#pragma once

typedef unsigned int UInt16;
class Sprite;
struct Vector2D;

class Animation {
	public:
	Animation(const char** targetFiles, UInt16 frameCount, UInt16 frameLength);
	Animation(const char** targetFiles, UInt16 frameCount, UInt16 frameLength, const Vector2D& origin);

	Animation(const char* targetSheet, UInt16 w, UInt16 h, UInt16 frameLength);
	Animation(const char* targetSheet, UInt16 w, UInt16 h, UInt16 frameLength, const Vector2D& origin);

	~Animation();

	void DrawFrame(const Vector2D& position);
	void DrawFrame(const Vector2D& position, bool flipH, bool flipV);
	void DrawFrame(const Vector2D& position, float rotation);
	void DrawFrame(const Vector2D& position, bool flipH, bool flipV, float rotation);

	private:
	UInt16 frameCount, frameLength;
	Sprite** frames;
};