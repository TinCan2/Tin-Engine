#pragma once

struct Vector2D;
struct SDL_Renderer;

struct Color;

class Painter {
	public:
	static void PaintPoint(const Vector2D& A);
	static void PaintLine(const Vector2D& A, const Vector2D& B);
	static void PaintRect(const Vector2D& A, const Vector2D& B, bool filled = false);
	static void PaintCircle(const Vector2D& O, float r);

	static void SetPaintColor(const Color& newColor);
	static Color GetPaintColor();

	private:
	Painter() = delete;
	~Painter() = delete;

	friend class GameManager;

	static Color* paintColor;
	static SDL_Renderer* boundedRenderer;
};