#include "Camera.h"
#include "Color.h"
#include "GameManager.h"
#include "DebugPainter.h"
#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <cmath>

//Renderer Access
void DebugPainter::PaintPoint(const Vector2D& A) {
	SDL_SetRenderDrawColor(boundedRenderer, paintColor->r, paintColor->g, paintColor->b, paintColor->a);
	GameManager::GetCurrentInstance()->ScheduleColorReset();

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPos(camera->GetPosition());
	cornerPos += Vector2D(-camera->GetExtents().x, camera->GetExtents().y);
	Vector2D DA = A - cornerPos;
	DA *= Vector2D::UnitPixelEquivalent;

	SDL_RenderDrawPoint(boundedRenderer, DA.x, -DA.y);
}

void DebugPainter::PaintLine(const Vector2D& A, const Vector2D& B) {
	SDL_SetRenderDrawColor(boundedRenderer, paintColor->r, paintColor->g, paintColor->b, paintColor->a);
	GameManager::GetCurrentInstance()->ScheduleColorReset();

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPos(camera->GetPosition());
	cornerPos += Vector2D(-camera->GetExtents().x, camera->GetExtents().y);
	Vector2D DA = A - cornerPos;
	Vector2D DB = B - cornerPos;
	DA *= Vector2D::UnitPixelEquivalent;
	DB *= Vector2D::UnitPixelEquivalent;

	SDL_RenderDrawLine(boundedRenderer, DA.x, -DA.y, DB.x, -DB.y);
}

void DebugPainter::PaintRect(const Vector2D& A, const Vector2D& B, bool filled) {
	SDL_SetRenderDrawColor(boundedRenderer, paintColor->r, paintColor->g, paintColor->b, paintColor->a);
	GameManager::GetCurrentInstance()->ScheduleColorReset();

	SDL_Rect dest;
	dest.w = fabs(A.x-B.x)*Vector2D::UnitPixelEquivalent;
	dest.h = fabs(A.y-B.y)*Vector2D::UnitPixelEquivalent;

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPos(camera->GetPosition());
	cornerPos += Vector2D(-camera->GetExtents().x, camera->GetExtents().y);
	Vector2D DA = A - cornerPos;
	Vector2D DB = B - cornerPos;

	dest.x = std::min(DA.x,DB.x)*Vector2D::UnitPixelEquivalent;
	dest.y = -std::max(DA.y,DB.y)*Vector2D::UnitPixelEquivalent;

	SDL_RenderDrawRect(boundedRenderer, &dest);
	filled ? SDL_RenderFillRect(boundedRenderer, &dest) : SDL_RenderDrawRect(boundedRenderer, &dest);
}

void DebugPainter::PaintRect(const Vector2D& center, const Vector2D& extents, float rotation) {
	SDL_SetRenderDrawColor(boundedRenderer, paintColor->r, paintColor->g, paintColor->b, paintColor->a);
	GameManager::GetCurrentInstance()->ScheduleColorReset();

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPos(camera->GetPosition());
	cornerPos += Vector2D(-camera->GetExtents().x, camera->GetExtents().y);

	int UPE = Vector2D::UnitPixelEquivalent;
	Vector2D rotatedExtentsA = extents.x*Vector2D(cos(rotation), sin(rotation)) + extents.y*Vector2D(-sin(rotation), cos(rotation));
	Vector2D rotatedExtentsB = extents.x*Vector2D(cos(rotation), sin(rotation)) - extents.y*Vector2D(-sin(rotation), cos(rotation));

	Vector2D DA = center + rotatedExtentsA - cornerPos;
	Vector2D DB = center - rotatedExtentsB - cornerPos;
	SDL_RenderDrawLine(boundedRenderer, DA.x*UPE, -DA.y*UPE, DB.x*UPE, -DB.y*UPE);

	DA = center - rotatedExtentsB - cornerPos;
	DB = center - rotatedExtentsA - cornerPos;
	SDL_RenderDrawLine(boundedRenderer, DA.x*UPE, -DA.y*UPE, DB.x*UPE, -DB.y*UPE);

	DA = center - rotatedExtentsA - cornerPos;
	DB = center + rotatedExtentsB - cornerPos;
	SDL_RenderDrawLine(boundedRenderer, DA.x*UPE, -DA.y*UPE, DB.x*UPE, -DB.y*UPE);

	DA = center + rotatedExtentsB - cornerPos;
	DB = center + rotatedExtentsA - cornerPos;
	SDL_RenderDrawLine(boundedRenderer, DA.x*UPE, -DA.y*UPE, DB.x*UPE, -DB.y*UPE);
}

void DebugPainter::PaintCircle(const Vector2D& O, float r){
	if(fabs(r)*Vector2D::UnitPixelEquivalent <= 0.5) return;

	SDL_SetRenderDrawColor(boundedRenderer, paintColor->r, paintColor->g, paintColor->b, paintColor->a);
	GameManager::GetCurrentInstance()->ScheduleColorReset();

	int n = ceil(M_PI/acos(1-0.5/(fabs(r)*Vector2D::UnitPixelEquivalent)));

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPos(camera->GetPosition());
	cornerPos += Vector2D(-camera->GetExtents().x, camera->GetExtents().y);

	for (int i = 0; i < n; i++) {
		Vector2D DA = O + r*Vector2D(cos(2*i*M_PI/n), sin(2*i*M_PI/n)) - cornerPos;
		Vector2D DB = O + r*Vector2D(cos(2*(i+1)*M_PI/n), sin(2*(i+1)*M_PI/n)) - cornerPos;
		DA *= Vector2D::UnitPixelEquivalent;
		DB *= Vector2D::UnitPixelEquivalent;
		SDL_RenderDrawLine(boundedRenderer, DA.x, -DA.y, DB.x, -DB.y);
	}
}

//Color Access
void DebugPainter::SetPaintColor(const Color& newColor) {
	*paintColor = newColor;
}

Color DebugPainter::GetPaintColor() {
	return *paintColor;
}


//Statics
Color* DebugPainter::paintColor = new Color(255, 255, 255);
SDL_Renderer* DebugPainter::boundedRenderer;