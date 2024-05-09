#include "Camera.h"
#include "Color.h"
#include "GameManager.h"
#include "Painter.h"
#include "Vector2D.h"
#include <cmath>
#include <SDL2/SDL.h>

#include <iostream>

using namespace Tin;

//Construction and Destruction
Painter::Painter() {
	this->paintColor = new Color(255,255,255);
}

Painter::Painter(const Color& paintColor) {
	this->paintColor = new Color(paintColor);
}

Painter::~Painter() {
	delete this->paintColor;
}


//Renderer Access
void Painter::PaintLine(const Vector2D& A, const Vector2D& B) const {
	GameManager::GetCurrentInstance()->ScheduleColorReset();
	SDL_SetRenderDrawColor(boundedRenderer, this->paintColor->r, this->paintColor->g, this->paintColor->b, this->paintColor->a);

	Vector2D cornerPos = Camera::GetCurrentInstance()->GetPosition() + Camera::GetCurrentInstance()->GetExtents().FlipH();
	Vector2D AtP = (A - cornerPos).FlipV() * Vector2D::UnitPixelEquivalent;
	Vector2D BtP = (B - cornerPos).FlipV() * Vector2D::UnitPixelEquivalent;

	SDL_RenderDrawLine(boundedRenderer, AtP.x, AtP.y, BtP.x, BtP.y);
}

void Painter::PaintCircle(const Vector2D& origin, const float& r, bool filled) const {
	float rA = fabs(r);
	if (rA < 0.5/Vector2D::UnitPixelEquivalent) return;

	int n = ceil(M_PI/acos(1 - 0.5/(rA*Vector2D::UnitPixelEquivalent)));

	Vector2D cornerPos = Camera::GetCurrentInstance()->GetPosition() + Camera::GetCurrentInstance()->GetExtents().FlipH();

	Vector2D* corners = new Vector2D[n](origin);
	for (int i=0; i<n; i++) {
		corners[i] += Vector2D(r*cos(2*i*M_PI/n), r*sin(2*i*M_PI/n));
		corners[i] = (corners[i]-cornerPos).FlipV()*Vector2D::UnitPixelEquivalent;
	}

	if (filled) {
		SDL_Vertex* vertices = new SDL_Vertex[n]();
		int* indices = new int[3*n]();

		for (int i=0; i<n; i++) {
			vertices[i].position = {corners[i].x, corners[i].y};
			vertices[i].color = {this->paintColor->r, this->paintColor->g, this->paintColor->b, this->paintColor->a};

			if (i < n-2) {
				indices[3*i] = 0;
				indices[3*i+1] = i+1;
				indices[3*i+2] = i+2;
			}
		}

		SDL_RenderGeometry(boundedRenderer, nullptr, vertices, n, indices, 3*n);

		delete[] vertices;
	}
	else {
		GameManager::GetCurrentInstance()->ScheduleColorReset();
		SDL_SetRenderDrawColor(boundedRenderer, this->paintColor->r, this->paintColor->g, this->paintColor->b, this->paintColor->a);

		for (int i=0; i<n; i++) {
			SDL_RenderDrawLine(boundedRenderer, corners[i].x, corners[i].y, corners[(i+1)%n].x, corners[(i+1)%n].y);
		}
	}

	delete[] corners;
}

void Painter::PaintRectangle(const Vector2D& center, const Vector2D& extents, bool filled, float rotation) const {
	if (fabs(extents.x) < 0.5/Vector2D::UnitPixelEquivalent || fabs(extents.y) < 0.5/Vector2D::UnitPixelEquivalent) return;

	Vector2D tExt = extents.x*Vector2D(cos(rotation),sin(rotation)) + extents.y*Vector2D(-sin(rotation),cos(rotation));
	Vector2D tExtF = -extents.x*Vector2D(cos(rotation),sin(rotation)) + extents.y*Vector2D(-sin(rotation),cos(rotation));

	Vector2D cornerPos = Camera::GetCurrentInstance()->GetPosition() + Camera::GetCurrentInstance()->GetExtents().FlipH();
	Vector2D corners[] = {center+tExt, center+tExtF, center-tExt, center-tExtF};

	for (int i=0; i<4; i++) corners[i] = (corners[i]-cornerPos).FlipV()*Vector2D::UnitPixelEquivalent;

	if (filled) {
		SDL_Vertex vertices[4];
		int indices[6];

		for (int i=0; i<4; i++) {
			vertices[i].position = {corners[i].x, corners[i].y};
			vertices[i].color = {this->paintColor->r, this->paintColor->g, this->paintColor->b, this->paintColor->a};

			if (i < 2) {
				indices[3*i] = 0;
				indices[3*i+1] = i+1;
				indices[3*i+2] = i+2;
			}
		}

		SDL_RenderGeometry(boundedRenderer, nullptr, vertices, 4, indices, 6);
	}
	else {
		GameManager::GetCurrentInstance()->ScheduleColorReset();
		SDL_SetRenderDrawColor(boundedRenderer, this->paintColor->r, this->paintColor->g, this->paintColor->b, this->paintColor->a);

		for (int i=0; i<4; i++) {
			SDL_RenderDrawLine(boundedRenderer, corners[i].x, corners[i].y, corners[(i+1)%4].x, corners[(i+1)%4].y);
		}
	}
}


//Color Access
Color Painter::GetPaintColor() const {
	return *this->paintColor;
}

void Painter::SetPaintColor(const Color& color) {
	*this->paintColor = color;
}

//Statics
SDL_Renderer* Painter::boundedRenderer;