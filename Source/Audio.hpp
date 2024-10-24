#pragma once
#include "DllMacro.hpp"
#include <map>

struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

namespace Tin {
	class TIN_API Audio {
		public:
		Audio(const char* targetFile, const bool& isMusic);

		Audio(const Audio& coppiedAudio);
		Audio& operator=(const Audio& coppiedAudio);

		~Audio();

		void Play(const bool& loop = false);

		private:
		const char* targetFile;
		bool isMusic;

		static void InitializeMixer();
		static void CloseMixer();
		friend class GameManager;

		struct Chunk{Mix_Chunk* mixChunk; size_t refCount;};
		struct Music{Mix_Music* mixMusic; size_t refCount;};

		static std::map<const char*, Chunk> chunkMap;
		static std::map<const char*, Music> musicMap;
	};
}