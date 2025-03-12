#ifndef IN_GAME_HPP
#define IN_GAME_HPP

#include <SDL.h>
#include "constants.hpp"
#include "game_states_manager.hpp"
#include "game_object.hpp"
#include "texture_manager.hpp"
#include "text_manager.hpp"
#include "audio_manager.hpp"

class InGame {
public:
	InGame(SDL_Renderer* renderer);
	~InGame();
	void CreateDisplay();
	void HandleInputs(SDL_Event& event);
	void Update();
	void Render();


private:
	SDL_Renderer* renderer;
	TextManager* textManager;
	TextureManager* textureManager;
	AudioManager* audioManager;

	// Background
	int backgroundDesertX;
	SDL_Texture* backgroundDesert;
	int backgroundDesertWidth, backgroundDesertHeight;
	SDL_Rect backgroundDesertDestRect1;
	SDL_Rect backgroundDesertDestRect2;
};

#endif