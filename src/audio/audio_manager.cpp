#include "audio_manager.hpp"

AudioManager::AudioManager() : music(nullptr) {
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) { // SDL_INIT_EVEVRYTHING doesn't init SDL_mixer 
		SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
	}
}

AudioManager::~AudioManager() {
	Clean();
	Mix_Quit();
}

Mix_Music* AudioManager::LoadMusic(const char* path) {
	music = Mix_LoadMUS(path);
	if (music == nullptr) {
		SDL_Log("Cannot load music: %s", path);
		return nullptr;
	}
	return music;
}

void AudioManager::PlayMusic(Mix_Music*, int loops) {
	if (music != nullptr) {
		Mix_PlayMusic(music, loops);
	}
}

void AudioManager::StopMusic() {
	Mix_HaltMusic();
}

void AudioManager::PauseMusic() {
	Mix_PauseMusic();
}

void AudioManager::ResumeMusic() {
	Mix_ResumeMusic();
}

Mix_Chunk* AudioManager::LoadSound(const char* path) {
	auto it = sounds.find(path);
	if (it != sounds.end()) {
		return sounds[path];
	}

	Mix_Chunk* chunk = Mix_LoadWAV(path);
	if (chunk == nullptr) {
		SDL_Log("Cannot load sound: %s", path);
		return nullptr;
	}
	sounds[path] = chunk;
	return chunk;
}

void AudioManager::PlaySound(Mix_Chunk* chunk, int loops) {
	Mix_PlayChannel(-1, chunk, loops);
}


void AudioManager::SetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

void AudioManager::SetSoundVolume(int volume) {
	for (auto& pair : sounds) {
		Mix_VolumeChunk(pair.second, volume);
	}
}

void AudioManager::Clean() {
	if (music != nullptr) {
		Mix_FreeMusic(music);
	}

	for (auto& pair : sounds) {
		Mix_FreeChunk(pair.second);
	}
	sounds.clear();
}