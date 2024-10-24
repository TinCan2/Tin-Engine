#pragma once
#include "DllMacro.hpp"
#include <vector>

namespace Tin {

	struct Vector2D;

	class Animation;
	class Sprite;

	class TIN_API VisualObject {
		public:
		VisualObject(const Vector2D& position, float depth, float rotation = 0);
		virtual ~VisualObject();

		VisualObject(const VisualObject& coppiedObject);
		VisualObject& operator=(const VisualObject& coppiedObject);

		void SetVisual(const Animation& animation);
		void SetVisual(const Sprite& sprite);
		Animation GetVisualAsAnimation() const;
		Sprite GetVisualAsSprite() const;

		void SetPosition(const Vector2D& position);
		Vector2D GetPosition() const;

		void SetRotation(const float& rotation);
		float GetRotation() const;

		void SetFlip(const bool& flipH, const bool& flipV);
		bool GetFlipH() const;
		bool GetFlipV() const;

		void SetDepth(const float& depth);
		float GetDepth() const;

		virtual void OnRender();

		private:
		void* visual;
		bool animated;

		Vector2D* position;
		float rotation;
		bool flipH, flipV;

		float depth;

		static bool CompareDepth(VisualObject* a, VisualObject* b);

		static void RenderObjects();
		friend class GameManager;

		static std::vector<VisualObject*> renderList;
	};
}