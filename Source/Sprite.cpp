#include "Camera.hpp"
#include "Sprite.hpp"
#include "Vector2D.hpp"
#include <cmath>
#include <numbers>
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

using namespace Tin;

//Texture Generation
void Sprite::GenerateTexture(const char* targetFile) {
	SDL_Texture* texture = IMG_LoadTexture(Sprite::boundedRenderer, targetFile);
	if (texture == nullptr) throw std::runtime_error("The requested texture could not be generated");
	Sprite::textureMap[targetFile] = {texture, 0};
}


//Construction and Destruction
Sprite::Sprite(const char* targetFile) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile].refCount++;

	this->origin = new Vector2D(0, 0);

	int textureWidth, textureHeight;
	SDL_QueryTexture(textureMap[targetFile].SDLTexture, nullptr, nullptr, &textureWidth, &textureHeight);

	this->w = textureWidth;
	this->h = textureHeight;

	this->x = this->y = 0;
}

Sprite::Sprite(const char* targetFile, const Vector2D& origin) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile].refCount++;

	this->origin = new Vector2D(origin);

	int textureWidth, textureHeight;
	SDL_QueryTexture(textureMap[targetFile].SDLTexture, nullptr, nullptr, &textureWidth, &textureHeight);

	this->w = textureWidth;
	this->h = textureHeight;

	this->x = this->y = 0;
}

Sprite::Sprite(const char* targetFile, cuint16_t& x, cuint16_t& y, cuint16_t& w, cuint16_t& h) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile].refCount++;

	this->origin = new Vector2D(0, 0);

	int textureHeight;
	SDL_QueryTexture(textureMap[targetFile].SDLTexture, nullptr, nullptr, nullptr, &textureHeight);

	this->w = w;
	this->h = h;

	this->x = x;
	this->y = textureHeight-h-y;
}

Sprite::Sprite(const char* targetFile, cuint16_t& x, cuint16_t& y, cuint16_t& w, cuint16_t& h, const Vector2D& origin) {
	if (!textureMap.contains(targetFile)) GenerateTexture(targetFile);

	this->boundTexture = targetFile;
	textureMap[targetFile].refCount++;

	this->origin = new Vector2D(origin);

	int textureHeight;
	SDL_QueryTexture(textureMap[targetFile].SDLTexture, nullptr, nullptr, nullptr, &textureHeight);

	this->w = w;
	this->h = h;

	this->x = x;
	this->y = textureHeight-h-y;
}

Sprite::Sprite(const Sprite& coppiedSprite) {
	this->boundTexture = coppiedSprite.boundTexture;
	textureMap[this->boundTexture].refCount++;

	this->origin = new Vector2D(*coppiedSprite.origin);

	this->x = coppiedSprite.x;
	this->y = coppiedSprite.y;
	this->w = coppiedSprite.w;
	this->h = coppiedSprite.h;
}

Sprite& Sprite::operator=(const Sprite& coppiedSprite) {
	textureMap[this->boundTexture].refCount--;
	if (textureMap[this->boundTexture].refCount == 0) {
		SDL_DestroyTexture(textureMap[this->boundTexture].SDLTexture);
		textureMap.erase(this->boundTexture);
	}

	this->boundTexture = coppiedSprite.boundTexture;
	textureMap[this->boundTexture].refCount++;

	*this->origin = *coppiedSprite.origin;

	this->x = coppiedSprite.x;
	this->y = coppiedSprite.y;
	this->w = coppiedSprite.w;
	this->h = coppiedSprite.h;

	return *this;
}

Sprite::~Sprite() {
	delete this->origin;

	textureMap[this->boundTexture].refCount--;
	if (textureMap[this->boundTexture].refCount == 0) {
		SDL_DestroyTexture(textureMap[this->boundTexture].SDLTexture);
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
        SDL_RenderCopyEx(boundedRenderer, textureMap[this->boundTexture].SDLTexture, &sourceRect, &destRect, 0, nullptr, flip);
    }
    else {
        float degRot = -180.0*rotation/M_PI;
    	SDL_Point rotationPoint(Vector2D::UnitPixelEquivalent*this->origin->x, this->h - Vector2D::UnitPixelEquivalent*this->origin->y);
    	SDL_Texture* sdlTexture = textureMap[this->boundTexture].SDLTexture;
    	SDL_RenderCopyEx(boundedRenderer, sdlTexture, &sourceRect, &destRect, degRot, &rotationPoint, flip);
    }
}


//Dimension Access
uint16_t Sprite::GetWidth() const {
	return this->w;
}

uint16_t Sprite::GetHeight() const {
	return this->h;
}

//Statics
SDL_Renderer* Sprite::boundedRenderer;
std::map<const char*, Sprite::Texture> Sprite::textureMap;