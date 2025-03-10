#ifndef OPTIONS_MENU_HPP
#define OPTIONS_MENU_HPP

#include <SDL.h>
#include "constants.hpp"
#include "text_manager.hpp"
#include "texture_manager.hpp"
#include "audio_manager.hpp"
#include "game_states_manager.hpp"

class OptionsMenu {
public:
	OptionsMenu(SDL_Renderer* renderer);
	~OptionsMenu();
	void CreateDisplay();
	void HandleInputs(SDL_Event& event);
	void Update();
	void Render();

private:
	int screenWidth, screenHeight;
	SDL_Renderer* renderer;
	TextureManager* textureManager;
	TextManager* textManager;
	AudioManager* audioManager;
	
	TTF_Font* font;
	SDL_Texture* optionsMenuBackground;

	SDL_Texture* fullScreenTexture;
	SDL_Rect fullScreenRect;

	SDL_Texture* SFXVolumeTexture;
	SDL_Rect SFXVolumeRect;

	SDL_Texture* musicVolumeTexture;
	SDL_Rect musicVolumeRect;
};

#endif