#include "Animation.h"
#include "GameManager.h"
#include "Sprite.h"
#include "Vector2D.h"

//Construction and Destruction
Animation::Animation(const char** targetFiles, UInt16 frameCount, UInt16 frameLength) {
	if (frameLength == 0) throw "Frame length cannot be zero.";

	this->frameCount = frameCount;
	this->frames = new Sprite*[frameCount];
	for (int i = 0; i < frameCount; i++) {
		this->frames[i] = new Sprite(targetFiles[i]);
	}

	this->frameLength = frameLength;
}

Animation::Animation(const char** targetFiles, UInt16 frameCount, UInt16 frameLength, const Vector2D& origin) {
	if (frameLength == 0) throw "Frame length cannot be zero.";

	this->frameCount = frameCount;
	this->frames = new Sprite*[frameCount];
	for (int i = 0; i < frameCount; i++) {
		this->frames[i] = new Sprite(targetFiles[i], origin);
	}

	this->frameLength = frameLength;
}

Animation::Animation(const char* targetSheet, UInt16 w, UInt16 h, UInt16 frameLength) {
	if (frameLength == 0) throw "Frame length cannot be zero.";

	Sprite sheet(targetSheet);

	UInt16 columns = sheet.GetWidth()/w;
	UInt16 rows = sheet.GetHeight()/h;

	this->frameCount = columns*rows;
	this->frames = new Sprite*[this->frameCount];
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++) this->frames[i*columns+j] = new Sprite(targetSheet, j*w, (rows-i-1)*h, w, h, Vector2D(0,0));
	}

	this->frameLength = frameLength;
}

Animation::Animation(const char* targetSheet, UInt16 w, UInt16 h, UInt16 frameLength, const Vector2D& origin) {
	if (frameLength == 0) throw "Frame length cannot be zero.";

	Sprite sheet(targetSheet);

	UInt16 columns = sheet.GetWidth()/w;
	UInt16 rows = sheet.GetHeight()/h;

	this->frameCount = columns*rows;
	this->frames = new Sprite*[this->frameCount];
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++) this->frames[i*columns+j] = new Sprite(targetSheet, j*w, (rows-i-1)*h, w, h, Vector2D(origin));
	}

	this->frameLength = frameLength;
}

Animation::~Animation() {
	for (int i = 0; i < this->frameCount; i++) {
		delete this->frames[i];
	}
	delete[] this->frames;
}


//Renderer Access
void Animation::DrawFrame(const Vector2D& position) {
	UInt16 currentFrame = (GameManager::GetCurrentInstance()->GetFrameCount() / this->frameLength) % this->frameCount;
	this->frames[currentFrame]->Draw(position);
}

void Animation::DrawFrame(const Vector2D& position, bool flipH, bool flipV) {
	UInt16 currentFrame = (GameManager::GetCurrentInstance()->GetFrameCount() / this->frameLength) % this->frameCount;
	this->frames[currentFrame]->Draw(position, flipH, flipV);
}

void Animation::DrawFrame(const Vector2D& position, float rotation) {
	UInt16 currentFrame = (GameManager::GetCurrentInstance()->GetFrameCount() / this->frameLength) % this->frameCount;
	this->frames[currentFrame]->Draw(position, rotation);
}

void Animation::DrawFrame(const Vector2D& position, bool flipH, bool flipV, float rotation) {
	UInt16 currentFrame = (GameManager::GetCurrentInstance()->GetFrameCount() / this->frameLength) % this->frameCount;
	this->frames[currentFrame]->Draw(position, flipH, flipV, rotation);
}