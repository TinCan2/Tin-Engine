#pragma once

namespace Tin {
	struct Vector2D;

	typedef unsigned int UInt16;

	class Camera {
		public:
		static Camera* GetCurrentInstance();

		Camera(const Camera&) = delete;

		Vector2D GetPosition() const;
		Vector2D GetExtents() const;

		private:
		Camera(const UInt16& w, const UInt16& h);
		~Camera();

		friend class GameManager;

		Vector2D* position;
		Vector2D* extents;

		static Camera* activeCamera;
	};
}