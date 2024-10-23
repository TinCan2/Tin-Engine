#pragma once
#include "DllMacro.hpp"
#include <vector>

namespace Tin {
	struct Vector2D;

	class Circle;
	class Rectangle;
	class JointShape;

	class CollisionInfo;

	typedef unsigned char UInt8;
	typedef unsigned long long UInt64;

	class TIN_API PhysicalObject {
		public:
		PhysicalObject(const Circle& collider, const float& mass);
		PhysicalObject(const Rectangle& collider, const float& mass);
		PhysicalObject(const JointShape& collider, const float& mass);

		PhysicalObject(const PhysicalObject& coppiedObject);
		PhysicalObject& operator=(const PhysicalObject& coppiedObject);

		~PhysicalObject();

		enum class ColliderTypes : UInt8 {Circle, Rectangle, JointShape};

		Circle GetColliderAsCircle() const;
		Rectangle GetColliderAsRectangle() const;
		JointShape GetColliderAsJointShape() const;

		ColliderTypes GetColliderType() const;

		Vector2D GetCenterOfMass() const;

		float GetMass() const;
		float GetMomentOfInertia() const;

		Vector2D GetVelocity() const;
		float GetAngularSpeed() const;

		void SetVelocity(const Vector2D& velocity);
		void SetAngularSpeed(const float& angularSpeed);

		float GetRestitutionCoefficient();
		void SetRestitutionCoefficient(const float& rCoeff);

		static float GetDeltaTime();

		private:
		void* collider;
		ColliderTypes colliderType;

		Vector2D* centerOfMass;

		float mass;
		float momentOfInertia;

		Vector2D* velocity;
		float angularSpeed;

		float rCoeff;

		static void ResolveCollision(PhysicalObject* const& bodyI, PhysicalObject* const& bodyJ, const CollisionInfo& collision);
		static void UpdateBodies();
		friend class GameManager;

		static std::vector<PhysicalObject*> bodyList;

		static UInt64 lastFrame;
		static UInt64 currentFrame;
	};
}