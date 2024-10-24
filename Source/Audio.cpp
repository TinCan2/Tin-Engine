#include "Audio.hpp"
#include <SDL_mixer.h>
#include <stdexcept>

#include <iostream>

using namespace Tin;

//Construction and Destruction
Audio::Audio(const char* targetFile, const bool& isMusic) {
	if (isMusic) {
		if (!musicMap.contains(targetFile)) {
			Mix_Music* generatedMusic = Mix_LoadMUS(targetFile);
			if (generatedMusic == nullptr) throw std::runtime_error("The requested audio file could not be loaded.");
			musicMap[targetFile] = Music(generatedMusic, 1);
		}
	}
	else {
		if (!chunkMap.contains(targetFile)) {
			Mix_Chunk* generatedChunk = Mix_LoadWAV(targetFile);
			if (generatedChunk == nullptr) throw std::runtime_error("The requested audio file could not be loaded.");
			chunkMap[targetFile] = Chunk(generatedChunk, 1);
		}
	}

	this->targetFile = targetFile;
	this->isMusic = isMusic;
}

Audio::Audio(const Audio& coppiedAudio) {
	this->targetFile = coppiedAudio.targetFile;
	this->isMusic = coppiedAudio.isMusic;

	this->isMusic ? musicMap[targetFile].refCount++ : chunkMap[targetFile].refCount++;
}

Audio& Audio::operator=(const Audio& coppiedAudio) {
	this->targetFile = coppiedAudio.targetFile;
	this->isMusic = coppiedAudio.isMusic;

	this->isMusic ? musicMap[targetFile].refCount++ : chunkMap[targetFile].refCount++;

	return *this;
}

Audio::~Audio() {
	if (isMusic) {
		musicMap[this->targetFile].refCount --;
		if (musicMap[this->targetFile].refCount == 0) {
			Mix_FreeMusic(musicMap[this->targetFile].mixMusic);
			musicMap.erase(this->targetFile);
		}
	}
	else {
		chunkMap[this->targetFile].refCount --;
		if (chunkMap[this->targetFile].refCount == 0) {
			Mix_FreeChunk(chunkMap[this->targetFile].mixChunk);
			chunkMap.erase(this->targetFile);
		}
	}
}


//Audio Functionality
void Audio::Play(const bool& loop) {
	if (this->isMusic) Mix_PlayMusic(musicMap[this->targetFile].mixMusic, !loop-1);
	else Mix_PlayChannel(-1, chunkMap[this->targetFile].mixChunk, 0);
}


//Mixer Access
void Audio::InitializeMixer() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void Audio::CloseMixer() {
	Mix_Quit();
}


//Statics
std::map<const char*, Audio::Chunk> Audio::chunkMap;
std::map<const char*, Audio::Music> Audio::musicMap;