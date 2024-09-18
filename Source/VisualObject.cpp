#include "Animation.hpp"
#include "Sprite.hpp"
#include "Vector2D.hpp"
#include "VisualObject.hpp"
#include <algorithm>

using namespace Tin;

//Consturction and Destruction
VisualObject::VisualObject(const Vector2D& position, float depth, float rotation) {
	this->visual = nullptr;

	this->position = new Vector2D(position);
	this->rotation = rotation;

	this->flipV = this->flipH = false;

	this->depth = depth;
	std::vector<VisualObject*>::iterator it = std::lower_bound(renderList.begin(), renderList.end(), this, CompareDepth);
	renderList.insert(it, this);
}

VisualObject::~VisualObject() {
	if (this->visual != nullptr) {
    	if (this->animated) delete static_cast<Animation*>(this->visual);
    	else static_cast<Sprite*>(this->visual);
	}

	delete this->position;

	std::pair<std::vector<VisualObject*>::iterator, std::vector<VisualObject*>::iterator> range;
	range = std::equal_range(renderList.begin(), renderList.end(), this, CompareDepth);
	renderList.erase(std::find(range.first, range.second, this));
}

VisualObject::VisualObject(const VisualObject& coppiedObject) {
	if (coppiedObject.visual == nullptr) this->visual == nullptr;
	else {
		if (coppiedObject.animated) this->visual = new Animation(*static_cast<Animation*>(coppiedObject.visual));
		else this->visual = new Sprite(*static_cast<Sprite*>(coppiedObject.visual));

		this->animated = coppiedObject.animated;
	}

	this->position = new Vector2D(*coppiedObject.position);
	this->rotation = coppiedObject.rotation;

	this->flipH = coppiedObject.flipH;
	this->flipV = coppiedObject.flipV;

	this->depth = depth;
	std::vector<VisualObject*>::iterator it = std::lower_bound(renderList.begin(), renderList.end(), this, CompareDepth);
	renderList.insert(it, this);
}

VisualObject& VisualObject::operator=(const VisualObject& coppiedObject) {
	if (this->visual != nullptr) {
    	if (this->animated) delete static_cast<Animation*>(this->visual);
    	else static_cast<Sprite*>(this->visual);
	}

	if (coppiedObject.visual == nullptr) this->visual == nullptr;
	else {
		if (coppiedObject.animated) this->visual = new Animation(*static_cast<Animation*>(coppiedObject.visual));
		else this->visual = new Sprite(*static_cast<Sprite*>(coppiedObject.visual));

		this->animated = coppiedObject.animated;
	}

	*this->position = *coppiedObject.position;
	this->rotation = coppiedObject.rotation;

	this->flipH = coppiedObject.flipH;
	this->flipV = coppiedObject.flipV;

	std::pair<std::vector<VisualObject*>::iterator, std::vector<VisualObject*>::iterator> range;
	range = std::equal_range(renderList.begin(), renderList.end(), this, CompareDepth);
	renderList.erase(std::find(range.first, range.second, this));

	this->depth = depth;
	std::vector<VisualObject*>::iterator it = std::lower_bound(renderList.begin(), renderList.end(), this, CompareDepth);
	renderList.insert(it, this);

	return *this;
}


//Member Access
void VisualObject::SetVisual(const Animation& animation) {
	if (this->visual != nullptr) {
		if (!this->animated) {
			delete static_cast<Sprite*>(this->visual);
			this->visual = new Animation(animation);
		}
		else *static_cast<Animation*>(this->visual) = animation;
	}
	else this->visual = new Animation(animation);

	this->animated = true;
}

void VisualObject::SetVisual(const Sprite& sprite) {
	if (this->visual != nullptr) {
		if (this->animated) {
			delete static_cast<Animation*>(this->visual);
			this->visual = new Sprite(sprite);
		}
		else *static_cast<Sprite*>(this->visual) = sprite;
	}
	else this->visual = new Sprite(sprite);

	this->animated = false;
}

Animation VisualObject::GetVisualAsAnimation() const {
	return *static_cast<Animation*>(this->visual);
}

Sprite VisualObject::GetVisualAsSprite() const {
	return *static_cast<Sprite*>(this->visual);
}

void VisualObject::SetPosition(const Vector2D& position) {
	*this->position = position;
}

Vector2D VisualObject::GetPosition() const {
	return *this->position;
}

void VisualObject::SetRotation(const float& rotation) {
	this->rotation = rotation;
}

float VisualObject::GetRotation() const {
	return this->rotation;
}

void VisualObject::SetFlip(const bool& flipH, const bool& flipV) {
	this->flipH = flipH;
	this->flipV = flipV;
}

bool VisualObject::GetFlipH() const {
	return this->flipH;
}

bool VisualObject::GetFlipV() const {
	return this->flipV;
}

void VisualObject::SetDepth(const float& depth) {
	std::pair<std::vector<VisualObject*>::iterator, std::vector<VisualObject*>::iterator> range;
	range = std::equal_range(renderList.begin(), renderList.end(), this, CompareDepth);
	renderList.erase(std::find(range.first, range.second, this));

	this->depth = depth;
	std::vector<VisualObject*>::iterator it = std::lower_bound(renderList.begin(), renderList.end(), this, CompareDepth);
	renderList.insert(it, this);
}

float VisualObject::GetDepth() const {
	return this->depth;
}


//Rendering Methods
void Tin::VisualObject::OnRender() {
	if (this->visual == nullptr) return;

	if (this->animated) {
		Animation* animation = static_cast<Animation*>(this->visual);
		animation->DrawFrame(*this->position, this->flipH, this->flipV, this->rotation);
	}
	else {
		Sprite* sprite = static_cast<Sprite*>(this->visual);
		sprite->Draw(*this->position, this->flipH, this->flipV, this->rotation);
	}
}


//Depth Check Helper
bool VisualObject::CompareDepth(VisualObject* a, VisualObject* b) {
	return a->depth < b->depth;
}


//Renderer Access
void VisualObject::RenderObjects() {
	for (size_t i = renderList.size(); i > 0; i--) renderList[i - 1]->OnRender();
}


//Statics
std::vector<VisualObject*> VisualObject::renderList;