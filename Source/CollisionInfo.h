#pragma once

namespace Tin {
	struct Vector2D;

	class CollisionInfo {
		public:
		CollisionInfo();

		~CollisionInfo();

		Vector2D GetNormal() const;
		Vector2D GetContact() const;

		private:
		CollisionInfo(const CollisionInfo& coppiedObject);
		CollisionInfo& operator=(const CollisionInfo& coppiedObject);

		Vector2D* normal;
		Vector2D* contact;

		friend class Circle;
		friend class Rectangle;
		friend class JointShape;
	};
}