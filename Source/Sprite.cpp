#include "Camera.h"
#include "Sprite.h"
#include "Vector2D.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

using namespace Tin;

//Texture Generation
void Sprite::GenerateTexture(const char* targetFile) {
	SDL_Texture* texture = IMG_LoadTexture(Sprite::boundedRenderer, targetFile);
	if (texture == nullptr) throw std::runtime_error("The requested texture could not be generated");
	Sprite::textureMap[targetFile] = new std::pair<SDL_Texture*, UInt16>(texture, 0);
}


//Construction and Destruction
Sprite::Sprite(const char* targetFile) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile]->second++;

	this->origin = new Vector2D(0, 0);

	int textureWidth, textureHeight;
	SDL_QueryTexture(textureMap[targetFile]->first, nullptr, nullptr, &textureWidth, &textureHeight);

	this->w = textureWidth;
	this->h = textureHeight;

	this->x = this->y = 0;
}

Sprite::Sprite(const char* targetFile, const Vector2D& origin) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile]->second++;

	this->origin = new Vector2D(origin);

	int textureWidth, textureHeight;
	SDL_QueryTexture(textureMap[targetFile]->first, nullptr, nullptr, &textureWidth, &textureHeight);

	this->w = textureWidth;
	this->h = textureHeight;

	this->x = this->y = 0;
}

Sprite::Sprite(const char* targetFile, const UInt16& x, const UInt16& y, const UInt16& w, const UInt16& h) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile]->second++;

	this->origin = new Vector2D(0, 0);

	int textureHeight;
	SDL_QueryTexture(textureMap[targetFile]->first, nullptr, nullptr, nullptr, &textureHeight);

	this->w = w;
	this->h = h;

	this->x = x;
	this->y = textureHeight-h-y;
}

Sprite::Sprite(const char* targetFile, const UInt16& x, const UInt16& y, const UInt16& w, const UInt16& h, const Vector2D& origin) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile]->second++;

	this->origin = new Vector2D(origin);

	int textureHeight;
	SDL_QueryTexture(textureMap[targetFile]->first, nullptr, nullptr, nullptr, &textureHeight);

	this->w = w;
	this->h = h;

	this->x = x;
	this->y = textureHeight-h-y;
}

Sprite::Sprite(const Sprite& coppiedSprite) {
	this->boundTexture = coppiedSprite.boundTexture;
	textureMap[this->boundTexture]->second++;

	this->origin = new Vector2D(*coppiedSprite.origin);

	this->x = coppiedSprite.x;
	this->y = coppiedSprite.y;
	this->w = coppiedSprite.w;
	this->h = coppiedSprite.h;
}

Sprite& Sprite::operator=(const Sprite& coppiedSprite) {
	textureMap[this->boundTexture]->second--;
	if (textureMap[this->boundTexture]->second == 0) {
		SDL_DestroyTexture(textureMap[this->boundTexture]->first);
		delete textureMap[this->boundTexture];
		textureMap.erase(this->boundTexture);
	}

	this->boundTexture = coppiedSprite.boundTexture;
	textureMap[this->boundTexture]->second++;

	*this->origin = *coppiedSprite.origin;

	this->x = coppiedSprite.x;
	this->y = coppiedSprite.y;
	this->w = coppiedSprite.w;
	this->h = coppiedSprite.h;

	return *this;
}

Sprite::~Sprite() {
	delete this->origin;

	textureMap[this->boundTexture]->second--;
	if (textureMap[this->boundTexture]->second == 0) {
		SDL_DestroyTexture(textureMap[this->boundTexture]->first);
		delete textureMap[this->boundTexture];
		textureMap.erase(this->boundTexture);
	}
}


//Renderer Access
void Sprite::Draw(const Vector2D& position, const bool& flipH, const bool& flipV, const float& rotation) const {
	SDL_Rect sourceRect, destRect;
	sourceRect.x = this->x;
	sourceRect.y = this->y;

	sourceRect.w = destRect.w = this->w;
	sourceRect.h = destRect.h = this->h;

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPos(camera->GetPosition());
	cornerPos += Vector2D(-camera->GetExtents().x, camera->GetExtents().y);

	Vector2D drawingPos = (position - cornerPos) - *this->origin;

	destRect.x = drawingPos.x * Vector2D::UnitPixelEquivalent;
	destRect.y = -drawingPos.y * Vector2D::UnitPixelEquivalent - this->h;

    SDL_RendererFlip flip = (SDL_RendererFlip)(flipH | (flipV<<1));
    if (fmod(rotation,2*M_PI) == 0){
        SDL_RenderCopyEx(boundedRenderer, textureMap[this->boundTexture]->first, &sourceRect, &destRect, 0, nullptr, flip);
    }
    else {
        float degRot = -180.0*rotation/M_PI;
    	SDL_Point rotationPoint(Vector2D::UnitPixelEquivalent*this->origin->x, this->h - Vector2D::UnitPixelEquivalent*this->origin->y);
    	SDL_RenderCopyEx(boundedRenderer, textureMap[this->boundTexture]->first, &sourceRect, &destRect, degRot, &rotationPoint, flip);
    }
}


//Dimension Access
UInt16 Sprite::GetWidth() const {
	return this->w;
}

UInt16 Sprite::GetHeight() const {
	return this->h;
}

//Statics
SDL_Renderer* Sprite::boundedRenderer;
std::map<const char*, std::pair<SDL_Texture*, UInt16>*> Sprite::textureMap;