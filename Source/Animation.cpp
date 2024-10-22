#include "Animation.hpp"
#include "GameManager.hpp"
#include "Sprite.hpp"
#include "Vector2D.hpp"
#include <stdexcept>

using namespace Tin;

//Construction and Destruction
Animation::Animation(const char** targetFiles, cuint16_t& frameCount, cuint16_t& frameLength) {
	if (frameLength == 0) throw std::runtime_error("Frame length cannot be zero.");

	this->frameCount = frameCount;
	this->frames = new std::shared_ptr<Sprite>[frameCount];
	for (int i = 0; i < frameCount; i++) {
		this->frames[i] = std::make_shared<Sprite>(targetFiles[i]);
	}

	this->frameLength = frameLength;
}

Animation::Animation(const char** targetFiles, cuint16_t& frameCount, cuint16_t& frameLength, const Vector2D& origin) {
	if (frameLength == 0) throw std::runtime_error("Frame length cannot be zero.");

	this->frameCount = frameCount;
	this->frames = new std::shared_ptr<Sprite>[frameCount];
	for (int i = 0; i < frameCount; i++) {
		this->frames[i] = std::make_shared<Sprite>(targetFiles[i], origin);
	}

	this->frameLength = frameLength;
}

Animation::Animation(const char* targetSheet, cuint16_t& w, cuint16_t& h, cuint16_t& frameLength) {
	if (frameLength == 0) throw std::runtime_error("Frame length cannot be zero.");

	Sprite sheet(targetSheet);

	UInt16 columns = sheet.GetWidth()/w;
	UInt16 rows = sheet.GetHeight()/h;

	this->frameCount = columns*rows;
	this->frames = new std::shared_ptr<Sprite>[this->frameCount];
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++) this->frames[i*columns+j] = std::make_shared<Sprite>(targetSheet, j*w, (rows-i-1)*h, w, h);
	}

	this->frameLength = frameLength;
}

Animation::Animation(const char* targetSheet, cuint16_t& w, cuint16_t& h, cuint16_t& frameLength, const Vector2D& origin) {
	if (frameLength == 0) throw std::runtime_error("Frame length cannot be zero.");

	Sprite sheet(targetSheet);

	UInt16 columns = sheet.GetWidth()/w;
	UInt16 rows = sheet.GetHeight()/h;

	this->frameCount = columns*rows;
	this->frames = new std::shared_ptr<Sprite>[this->frameCount];
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++) this->frames[i*columns+j] = std::make_shared<Sprite>(targetSheet, j*w, (rows-i-1)*h, w, h, origin);
	}

	this->frameLength = frameLength;
}

Animation::Animation(const Animation& coppiedAnimation) {
	this->frameCount = coppiedAnimation.frameCount;
	this->frames = new std::shared_ptr<Sprite>[frameCount];
	for (int i = 0; i < frameCount; i++) {
		this->frames[i] = coppiedAnimation.frames[i];
	}

	this->frameLength = coppiedAnimation.frameLength;
}

Animation& Animation::operator=(const Animation& coppiedAnimation) {
	delete[] this->frames;

	this->frameCount = coppiedAnimation.frameCount;
	this->frames = new std::shared_ptr<Sprite>[frameCount];
	for (int i = 0; i < frameCount; i++) {
		this->frames[i] = coppiedAnimation.frames[i];
	}

	this->frameLength = coppiedAnimation.frameLength;

	return *this;
}

Animation::~Animation() {
	delete[] this->frames;
}


//Renderer Access
void Animation::DrawFrame(const Vector2D& position, const bool& flipH, const bool& flipV, const float& rotation) const {
	UInt16 currentFrame = (GameManager::GetCurrentInstance()->GetFrameCount() / this->frameLength) % this->frameCount;
	this->frames[currentFrame]->Draw(position, flipH, flipV, rotation);
}