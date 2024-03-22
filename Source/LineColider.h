#pragma once

struct Vector2D;

class LineColider {
	public:
	enum class LineType {
		Segment,
		Ray,
		Line
	};

	LineColider(const Vector2D& base, const Vector2D& tip);
	LineColider(const Vector2D& base, const Vector2D& tip, LineType type);
	~LineColider();

	LineColider(const LineColider& coppiedColider);

	Vector2D GetBase();
	Vector2D GetTip();
	LineType GetType();

	static bool Coliding(const LineColider& coliderA, const LineColider& coliderB);

	void Visualize();

	private:
	Vector2D* base;
	Vector2D* tip;

	LineType type;
};