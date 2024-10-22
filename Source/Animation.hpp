#pragma once
#include <cstdint>
#include <memory>

namespace Tin {

	class Sprite;
	struct Vector2D;

	typedef const uint16_t cuint16_t;

	class Animation {
		public:
		Animation(const char** targetFiles, cuint16_t& frameCount, cuint16_t& frameLength);
		Animation(const char** targetFiles, cuint16_t& frameCount, cuint16_t& frameLength, const Vector2D& origin);

		Animation(const char* targetSheet, cuint16_t& w, cuint16_t& h, cuint16_t& frameLength);
		Animation(const char* targetSheet, cuint16_t& w, cuint16_t& h, cuint16_t& frameLength, const Vector2D& origin);

		Animation(const Animation& coppiedAnimation);
		Animation& operator=(const Animation& coppiedAnimation);

		~Animation();

		void DrawFrame(const Vector2D& position, const bool& flipH=false, const bool& flipV=false, const float& rotation=0) const;

		private:
		uint16_t frameCount, frameLength;
		std::shared_ptr<Sprite>* frames;
	};
}