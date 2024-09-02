#pragma once
#include "DllMacro.hpp"
#include <memory>

namespace Tin {
	typedef unsigned int UInt16;

	class Sprite;
	struct Vector2D;

	class TIN_API Animation {
		public:
		Animation(const char** targetFiles, const UInt16& frameCount, const UInt16& frameLength);
		Animation(const char** targetFiles, const UInt16& frameCount, const UInt16& frameLength, const Vector2D& origin);

		Animation(const char* targetSheet, const UInt16& w, const UInt16& h, const UInt16& frameLength);
		Animation(const char* targetSheet, const UInt16& w, const UInt16& h, const UInt16& frameLength, const Vector2D& origin);

		Animation(const Animation& coppiedAnimation);
		Animation& operator=(const Animation& coppiedAnimation);

		~Animation();

		void DrawFrame(const Vector2D& position, const bool& flipH=false, const bool& flipV=false, const float& rotation=0) const;

		private:
		UInt16 frameCount, frameLength;
		std::shared_ptr<Sprite>* frames;
	};
}