#pragma once

struct SDL_Renderer;

namespace Tin {
	struct Color;
	struct Vector2D;

	class Painter {
		public:
		Painter();
		Painter(const Color& paintColor);
		~Painter();

		void PaintLine(const Vector2D& A, const Vector2D& B) const;
		void PaintCircle(const Vector2D& origin, const float& r, bool filled=false) const;
		void PaintRectangle(const Vector2D& center, const Vector2D& extents, bool filled=false, float rotation=0) const;

		Color GetPaintColor() const;
		void SetPaintColor(const Color& color);

		private:
		Color* paintColor;

		friend class GameManager;

		static SDL_Renderer* boundedRenderer;
	};
}