#include "CollisionInfo.hpp"
#include "Vector2D.hpp"

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

CollisionInfo::CollisionInfo(const CollisionInfo& coppiedObject) {
	this->contact = new Vector2D(*coppiedObject.contact);
	this->normal = new Vector2D(*coppiedObject.normal);
}

CollisionInfo& CollisionInfo::operator=(const CollisionInfo& coppiedObject) {
	*this->contact = *coppiedObject.contact;
	*this->normal = *coppiedObject.normal;
	return *this;
}


//Component Access
Vector2D CollisionInfo::GetNormal() const {
	return *this->normal;
}

Vector2D CollisionInfo::GetContact() const {
	return *this->contact;
}