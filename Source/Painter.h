#pragma once

struct SDL_Renderer;

namespace Tin {
	struct Color;
	struct Vector2D;

	class Circle;
	class JointShape;
	class Rectangle;

	class Painter {
		public:
		Painter();
		Painter(const Color& paintColor);

		Painter(const Painter& copiedPainter);
		Painter& operator=(const Painter& copiedPainter);

		~Painter();

		void PaintLine(const Vector2D& A, const Vector2D& B) const;
		void PaintCircle(const Circle& circle, const bool& filled=false) const;
		void PaintRectangle(const Rectangle& rectangle, const bool& filled=false) const;
		void PaintJointShape(const JointShape& jointShape, const bool& filled=false) const;

		Color GetPaintColor() const;
		void SetPaintColor(const Color& color);

		private:
		Color* paintColor;

		friend class GameManager;

		static SDL_Renderer* boundedRenderer;
	};
}