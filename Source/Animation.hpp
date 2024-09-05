#pragma once
#include "DllMacro.hpp"
#include <memory>

namespace Tin {
	typedef unsigned int uint16_t;

	class Sprite;
	struct Vector2D;

	class TIN_API Animation {
		public:
		Animation(const char** targetFiles, const uint16_t& frameCount, const uint16_t& frameLength);
		Animation(const char** targetFiles, const uint16_t& frameCount, const uint16_t& frameLength, const Vector2D& origin);

		Animation(const char* targetSheet, const uint16_t& w, const uint16_t& h, const uint16_t& frameLength);
		Animation(const char* targetSheet, const uint16_t& w, const uint16_t& h, const uint16_t& frameLength, const Vector2D& origin);

		Animation(const Animation& coppiedAnimation);
		Animation& operator=(const Animation& coppiedAnimation);

		~Animation();

		void DrawFrame(const Vector2D& position, const bool& flipH=false, const bool& flipV=false, const float& rotation=0) const;

		private:
		uint16_t frameCount, frameLength;
		std::shared_ptr<Sprite>* frames;
	};
}