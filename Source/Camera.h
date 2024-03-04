#pragma once

struct Vector2D;

typedef unsigned int UInt16;

class Camera {
	public:
	static Camera* GetCurrentInstance();

	Camera(const Camera&) = delete;

	Vector2D GetPosition();
	Vector2D GetExtents();

	private:
	Camera(UInt16 w, UInt16 h);
	~Camera();

	friend class GameManager;

	Vector2D* position;
	Vector2D* extents;

	static Camera* activeCamera;
};