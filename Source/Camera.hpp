#pragma once
#include <cstdint>

namespace Tin {
	struct Vector2D;

	class Camera {
		public:
		static Camera* GetCurrentInstance();

		Camera(const Camera&) = delete;

		Vector2D GetPosition() const;
		Vector2D GetExtents() const;

		private:
		Camera(const uint16_t& w, const uint16_t& h);
		~Camera();

		friend class GameManager;

		Vector2D* position;
		Vector2D* extents;

		static Camera* activeCamera;
	};
}