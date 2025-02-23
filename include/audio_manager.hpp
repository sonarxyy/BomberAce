#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <SDL.h>
#include <SDL_mixer.h>
#include <map>

class AudioManager {
public:
	AudioManager();
	~AudioManager();

	// For BGM
	Mix_Music* LoadMusic(const char* path);
	void PlayMusic(Mix_Music* music, int loops = -1); // - 1 for infinite loop
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();

	// For SFX
	Mix_Chunk* LoadSound(const char* path);
	void PlaySound(Mix_Chunk* chunk, int loops = 0);

	// Set volume
	void SetMusicVolume(int volume);
	void SetSoundVolume(int volume);

	void Clean();

private:
	Mix_Music* music; // store music
	std::map<const char*, Mix_Chunk*> sounds; // store SFX
};

#endif