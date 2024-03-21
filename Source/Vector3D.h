#pragma once

struct Vector2D;

struct Vector3D {
	float x, y, z;

	Vector3D();
	Vector3D(float x, float y, float z);

	Vector3D(const Vector3D& coppiedVector);

	float GetMagnitude();
	float GetMagnitude2();

	friend Vector3D operator+(const Vector3D& a, const Vector3D& b);

	friend Vector3D operator+=(Vector3D& a, const Vector3D& b);

	friend Vector3D operator-(const Vector3D& a);
	friend Vector3D operator-(const Vector3D& a, const Vector3D& b);

	friend Vector3D operator-=(Vector3D& a, const Vector3D& b);

	friend Vector3D operator*(const Vector3D& a, const float& b);
	friend Vector3D operator*(const float& a, const Vector3D& b);
	friend float operator*(const Vector3D& a, const Vector3D& b);

	friend Vector3D operator*=(Vector3D& a, const float& b);

	friend Vector3D operator/(const Vector3D& a, const float& b);

	friend Vector3D operator/=(Vector3D& a, const float& b);

	friend bool operator==(const Vector3D& a, const Vector3D& b);

	friend Vector3D operator^(const Vector3D& a, const Vector3D& b);

	explicit operator Vector2D();
};