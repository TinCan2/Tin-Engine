#include "Circle.hpp"
#include "JointShape.hpp"
#include "ModuleDefinitions.hpp"
#include "PhysicalObject.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"
#include <algorithm>
#include <cmath>
#include <numbers>
#include <SDL.h>
#include <stdexcept>

#ifdef TIN_MODULES_INCLUDE_VISUALS
	#include "VisualObject.hpp"
#endif

#include <iostream>

using namespace Tin;

//Construction and Destruction
PhysicalObject::PhysicalObject(const Circle& collider, const float& mass) {
	if (mass <= 0) throw std::runtime_error("Invalid mass.");
	this->collider = new Circle(collider);
	this->colliderType = ColliderTypes::Circle;

	this->centerOfMass = new Vector2D(collider.GetCenter());

	this->mass = mass;
	float r = collider.GetRadius();
	this->momentOfInertia = mass*r*r/2;

	this->velocity = new Vector2D();
	this->angularSpeed = 0;

	this->rCoeff = 1;

	this->lockRotation = false;

	bodyList.push_back(this);
}

PhysicalObject::PhysicalObject(const Rectangle& collider, const float& mass) {
	if (mass <= 0) throw std::runtime_error("Invalid mass.");
	this->collider = new Rectangle(collider);
	this->colliderType = ColliderTypes::Rectangle;

	this->centerOfMass = new Vector2D(collider.GetCenter());

	this->mass = mass;
	this->momentOfInertia = mass*collider.GetExtents().GetMagnitude2()/3;

	this->velocity = new Vector2D();
	this->angularSpeed = 0;

	this->rCoeff = 1;

	this->lockRotation = false;

	bodyList.push_back(this);
}

PhysicalObject::PhysicalObject(const JointShape& collider, const float& mass) {
	if (mass <= 0) throw std::runtime_error("Invalid mass.");
	this->collider = new JointShape(collider);
	this->colliderType = ColliderTypes::JointShape;

	this->centerOfMass = new Vector2D();
	float totalArea = 0;
	for (size_t i = 0; i < collider.GetCircleCount(); i++) {
		Vector2D center = collider.GetCircle(i).GetCenter();
		float r = collider.GetCircle(i).GetRadius();

		float area = std::numbers::pi*r*r;
		*this->centerOfMass += area*center;
		totalArea += area;
	}
	for (size_t i = 0; i < collider.GetRectangleCount(); i++) {
		Vector2D center = collider.GetRectangle(i).GetCenter();
		Vector2D ext = collider.GetRectangle(i).GetExtents();

		float area = 4*ext.x*ext.y;
		*this->centerOfMass += area*center;
		totalArea += area;
	}
	*centerOfMass /= totalArea;

	this->mass = mass;
	this->momentOfInertia = 0;
	float density = mass/totalArea;
	for (size_t i = 0; i < collider.GetCircleCount(); i++) {
		Vector2D center = collider.GetCircle(i).GetCenter();
		float r = collider.GetCircle(i).GetRadius();

		float area = std::numbers::pi*r*r;
		this->momentOfInertia += area*density*r*r/2;
		this->momentOfInertia += area*density*(center - *this->centerOfMass).GetMagnitude2();
	}
	for (size_t i = 0; i < collider.GetRectangleCount(); i++) {
		Vector2D center = collider.GetRectangle(i).GetCenter();
		Vector2D ext = collider.GetRectangle(i).GetExtents();

		float area = 4*ext.x*ext.y;
		this->momentOfInertia += area*density*ext.GetMagnitude2()/3;
		this->momentOfInertia += area*density*(center - *this->centerOfMass).GetMagnitude2();
	}

	this->velocity = new Vector2D();
	this->angularSpeed = 0;

	this->rCoeff = 1;

	this->lockRotation = false;

	bodyList.push_back(this);
}

PhysicalObject::PhysicalObject(const PhysicalObject& coppiedObject) {
	switch (coppiedObject.colliderType) {
		case ColliderTypes::Circle:
			this->collider = new Circle(*static_cast<Circle*>(coppiedObject.collider));
			break;
		case ColliderTypes::Rectangle:
			this->collider = new Rectangle(*static_cast<Rectangle*>(coppiedObject.collider));
			break;
		case ColliderTypes::JointShape:
			this->collider = new JointShape(*static_cast<JointShape*>(coppiedObject.collider));
			break;
	}
	this->colliderType = coppiedObject.colliderType;

	this->centerOfMass = new Vector2D(*coppiedObject.centerOfMass);

	this->mass = coppiedObject.mass;
	this->momentOfInertia = coppiedObject.momentOfInertia;

	this->velocity = new Vector2D(*coppiedObject.velocity);
	this->angularSpeed = coppiedObject.angularSpeed;

	this->rCoeff = coppiedObject.rCoeff;

	this->lockRotation = coppiedObject.lockRotation;

	bodyList.push_back(this);
}

PhysicalObject& PhysicalObject::operator=(const PhysicalObject& coppiedObject) {
	switch (coppiedObject.colliderType) {
		case ColliderTypes::Circle:
			*static_cast<Circle*>(this->collider) = *static_cast<Circle*>(coppiedObject.collider);
			break;
		case ColliderTypes::Rectangle:
			*static_cast<Rectangle*>(this->collider) = *static_cast<Rectangle*>(coppiedObject.collider);
			break;
		case ColliderTypes::JointShape:
			*static_cast<JointShape*>(this->collider) = *static_cast<JointShape*>(coppiedObject.collider);
			break;
	}
	this->colliderType = coppiedObject.colliderType;

	*this->centerOfMass = *coppiedObject.centerOfMass;

	this->mass = coppiedObject.mass;
	this->momentOfInertia = coppiedObject.momentOfInertia;

	*this->velocity = *coppiedObject.velocity;
	this->angularSpeed = coppiedObject.angularSpeed;

	this->rCoeff = coppiedObject.rCoeff;

	this->lockRotation = coppiedObject.lockRotation;

	bodyList.push_back(this);

	return *this;
}

PhysicalObject::~PhysicalObject() {
	switch (this->colliderType) {
		case ColliderTypes::Circle:
			delete static_cast<Circle*>(this->collider);
			break;
		case ColliderTypes::Rectangle:
			delete static_cast<Rectangle*>(this->collider);
			break;
		case ColliderTypes::JointShape:
			delete static_cast<JointShape*>(this->collider);
			break;
	}

	delete this->centerOfMass;
	delete this->velocity;

	std::vector<PhysicalObject*>::iterator it = std::find(bodyList.begin(), bodyList.end(), this);
	bodyList.erase(it);
}


//Member Getters
Circle PhysicalObject::GetColliderAsCircle() const {
	if (this->colliderType != ColliderTypes::Circle) throw std::runtime_error("Invalid colider type requested.");
	return *static_cast<Circle*>(this->collider);
}

Rectangle PhysicalObject::GetColliderAsRectangle() const {
	if (this->colliderType != ColliderTypes::Rectangle) throw std::runtime_error("Invalid colider type requested.");
	return *static_cast<Rectangle*>(this->collider);
}

JointShape PhysicalObject::GetColliderAsJointShape() const {
	if (this->colliderType != ColliderTypes::JointShape) throw std::runtime_error("Invalid colider type requested.");
	return *static_cast<JointShape*>(this->collider);
}

PhysicalObject::ColliderTypes PhysicalObject::GetColliderType() const {
	return this->colliderType;
}

Vector2D PhysicalObject::GetCenterOfMass() const {
	return *this->centerOfMass;
}

float PhysicalObject::GetMass() const {
	return this->mass;
}

float PhysicalObject::GetMomentOfInertia() const {
	return this->momentOfInertia;
}

Vector2D PhysicalObject::GetVelocity() const {
	return *this->velocity;
}

float PhysicalObject::GetAngularSpeed() const {
	return this->angularSpeed;
}

float PhysicalObject::GetRestitutionCoefficient() const {
	return this->rCoeff;
}

bool PhysicalObject::GetLockRotation() const {
	return this->lockRotation;
}


//Physics Globals
float PhysicalObject::GetDeltaTime() {
	return (currentFrame - lastFrame)/1000.0f;
}


//Member Setters
void PhysicalObject::SetVelocity(const Vector2D& velocity) {
	*this->velocity = velocity;
}

void PhysicalObject::SetAngularSpeed(const float& angularSpeed) {
	this->angularSpeed = angularSpeed;
}

void PhysicalObject::SetRestitutionCoefficient(const float& rCoeff) {
	if (rCoeff > 1 || rCoeff < 0) throw "Invalid coefficient of restitution.";
	this->rCoeff = rCoeff;
}

void PhysicalObject::SetLockRotation(const bool& lockRotation) {
	this->lockRotation = true;
}


//Body Access
void PhysicalObject::OnCollision(Vector2D contact, Vector2D normal) {}

void PhysicalObject::ResolveCollision(PhysicalObject* const& bodyI, PhysicalObject* const& bodyJ, const Vector2D& contact, const Vector2D& normal) {
	Vector2D unitNorm = normal/normal.GetMagnitude();

	bodyI->OnCollision(contact, normal);
	bodyJ->OnCollision(contact, normal);

	Vector2D dirI = contact - *bodyI->centerOfMass;
	Vector2D dirJ = contact - *bodyJ->centerOfMass;
	Vector2D tanI = Vector2D(-dirI.y, dirI.x);
	Vector2D tanJ = Vector2D(-dirJ.y, dirJ.x);

	Vector2D cVelI = *bodyI->velocity + tanI*bodyI->angularSpeed;
	Vector2D cVelJ = *bodyJ->velocity + tanJ*bodyJ->angularSpeed;

	float invMassI = 1/bodyI->mass;
	float invMassJ = 1/bodyJ->mass;

	float normalRelativeVelocity = (cVelJ - cVelI)*unitNorm;
	if (normalRelativeVelocity <= 0) {
		float compositeRCoeff = bodyI->rCoeff*bodyJ->rCoeff;

		float impulse = -(1+compositeRCoeff)*normalRelativeVelocity;
		impulse += 0.2*std::max(0.0, normal.GetMagnitude()-0.01)/GetDeltaTime(); //Might be limited to low velocity cases

		float crossI = dirI^unitNorm;
		float crossJ = dirJ^unitNorm;

		float denom = invMassI + invMassJ;
		if (!bodyI->lockRotation) denom += crossI*crossI/bodyI->momentOfInertia;
		if (!bodyJ->lockRotation) denom += crossJ*crossJ/bodyJ->momentOfInertia;
		impulse /= denom;

		*bodyI->velocity -= unitNorm*impulse*invMassI;
		*bodyJ->velocity += unitNorm*impulse*invMassJ;

		if (!bodyI->lockRotation) bodyI->angularSpeed -= impulse*crossI/bodyI->momentOfInertia;
		if (!bodyJ->lockRotation) bodyJ->angularSpeed += impulse*crossJ/bodyJ->momentOfInertia;

		if (fabs(bodyI->angularSpeed) < 0.01) bodyI->angularSpeed *= 0.5;
		if (fabs(bodyJ->angularSpeed) < 0.01) bodyJ->angularSpeed *= 0.5;
	}
}

void PhysicalObject::UpdateBodies() {
	lastFrame = currentFrame;
	currentFrame = SDL_GetTicks64();

	for (size_t i = 0; i < bodyList.size(); i++) {
		PhysicalObject* currentBody = bodyList[i];
		float theta = currentBody->angularSpeed*GetDeltaTime();
		Vector2D displacement = (*currentBody->velocity)*GetDeltaTime();
		switch (currentBody->colliderType) {
			case ColliderTypes::Circle: {
				Circle* circleBody = static_cast<Circle*>(currentBody->collider);
				circleBody->SetCenter(circleBody->GetCenter() + displacement);
				break;
			}
			case ColliderTypes::Rectangle: {
				Rectangle* rectangleBody = static_cast<Rectangle*>(currentBody->collider);
				rectangleBody->SetOrientation(rectangleBody->GetOrientation() + theta);
				rectangleBody->SetCenter(rectangleBody->GetCenter() + displacement);
				break;
			}
			case ColliderTypes::JointShape: {
				JointShape* jointBody = static_cast<JointShape*>(currentBody->collider);
				Vector2D dir = jointBody->GetCenter() - *currentBody->centerOfMass;
				Vector2D tDir = dir.x*Vector2D(std::cos(theta), std::sin(theta)) + dir.y*Vector2D(-std::sin(theta), std::cos(theta));

				jointBody->SetCenter(*currentBody->centerOfMass + tDir);
				jointBody->SetOrientation(jointBody->GetOrientation() + theta);

				jointBody->SetCenter(jointBody->GetCenter() + displacement);
				break;
			}
		}
		*currentBody->centerOfMass += displacement;

		#ifdef TIN_MODULES_INCLUDE_VISUALS
			VisualObject* visual = dynamic_cast<VisualObject*>(currentBody);
			if (visual != nullptr) {
				visual->SetPosition(visual->GetPosition() + displacement);
				visual->SetRotation(visual->GetRotation() + theta);
			}
		#endif
	}

	Vector2D contact, normal;
	for (size_t i = 0; i + 1 < bodyList.size(); i++) {
		for (size_t j = i+1; j < bodyList.size(); j++) {
			int collisionPair = 10*(static_cast<int>(bodyList[i]->colliderType)+1);
			collisionPair += static_cast<int>(bodyList[j]->colliderType)+1;

			bool colliding = false;
			switch (collisionPair) {
				case 11: {
					Circle* bodyI = static_cast<Circle*>(bodyList[i]->collider);
					Circle* bodyJ = static_cast<Circle*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 12: {
					Circle* bodyI = static_cast<Circle*>(bodyList[i]->collider);
					Rectangle* bodyJ = static_cast<Rectangle*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 13: {
					Circle* bodyI = static_cast<Circle*>(bodyList[i]->collider);
					JointShape* bodyJ = static_cast<JointShape*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 21: {
					Rectangle* bodyI = static_cast<Rectangle*>(bodyList[i]->collider);
					Circle* bodyJ = static_cast<Circle*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 22: {
					Rectangle* bodyI = static_cast<Rectangle*>(bodyList[i]->collider);
					Rectangle* bodyJ = static_cast<Rectangle*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 23: {
					Rectangle* bodyI = static_cast<Rectangle*>(bodyList[i]->collider);
					JointShape* bodyJ = static_cast<JointShape*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 31: {
					JointShape* bodyI = static_cast<JointShape*>(bodyList[i]->collider);
					Circle* bodyJ = static_cast<Circle*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 32: {
					JointShape* bodyI = static_cast<JointShape*>(bodyList[i]->collider);
					Rectangle* bodyJ = static_cast<Rectangle*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
				case 33: {
					JointShape* bodyI = static_cast<JointShape*>(bodyList[i]->collider);
					JointShape* bodyJ = static_cast<JointShape*>(bodyList[j]->collider);
					colliding = bodyI->CollidesWith(*bodyJ, &contact, &normal);
					break;
				}
			}

			if (colliding) ResolveCollision(bodyList[i], bodyList[j], contact, normal);
		}
	}
}

//Statics
std::vector<PhysicalObject*> PhysicalObject::bodyList;

uint64_t PhysicalObject::lastFrame = 0, PhysicalObject::currentFrame = 0;