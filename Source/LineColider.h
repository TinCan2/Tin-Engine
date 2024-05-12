#pragma once

namespace Tin {
	struct Vector2D;

	class LineColider {
		public:
		LineColider(const Vector2D& base, const Vector2D& tip);
		~LineColider();

		Vector2D GetBase() const;
		Vector2D GetTip() const;

		private:
		Vector2D* base;
		Vector2D* tip;
	};
}