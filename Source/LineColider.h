#pragma once

namespace Tin {
	struct Vector2D;

	class CircleColider;
	class RectColider;

	class LineColider {
		public:
		LineColider(const Vector2D& base, const Vector2D& tip);
		~LineColider();

		Vector2D GetBase() const;
		Vector2D GetTip() const;

		bool ColidesWith(const CircleColider& otherColider);
		bool ColidesWith(const LineColider& otherColider);
		bool ColidesWith(const RectColider& otherColider);

		private:
		Vector2D* base;
		Vector2D* tip;
	};
}