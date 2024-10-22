#include "CollisionInfo.h"
#include "Vector2D.h"

using namespace Tin;

//Construction and Destruction
CollisionInfo::CollisionInfo() {
	this->contact = new Vector2D();
	this->normal = new Vector2D();
}

CollisionInfo::~CollisionInfo() {
	delete this->contact;
	delete this->normal;
}


//Component Access
Vector2D CollisionInfo::GetNormal() const {
	return *this->normal;
}

Vector2D CollisionInfo::GetContact() const {
	return *this->contact;
}