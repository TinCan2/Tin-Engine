#pragma once
#include <memory>

namespace Tin {
	typedef unsigned int UInt16;

	class Sprite;
	struct Vector2D;

	class Animation {
		public:
		Animation(const char** targetFiles, UInt16 frameCount, UInt16 frameLength);
		Animation(const char** targetFiles, UInt16 frameCount, UInt16 frameLength, const Vector2D& origin);

		Animation(const char* targetSheet, UInt16 w, UInt16 h, UInt16 frameLength);
		Animation(const char* targetSheet, UInt16 w, UInt16 h, UInt16 frameLength, const Vector2D& origin);

		Animation(const Animation& coppiedAnimation);
		Animation& operator=(const Animation& coppiedAnimation);

		~Animation();

		void DrawFrame(const Vector2D& position, bool flipH=false, bool flipV=false, float rotation=0) const;

		private:
		UInt16 frameCount, frameLength;
		std::shared_ptr<Sprite>* frames;
	};
}