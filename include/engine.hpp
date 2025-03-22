#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include "in_game.hpp"
#include "main_menu.hpp"
#include "options_menu.hpp"
#include "constants.hpp"
#include "text_manager.hpp"
#include "texture_manager.hpp"
#include "audio_manager.hpp"
#include "game_states_manager.hpp"
#include "fade_transition.hpp"

class Player;

class Engine {
public:
	Engine(const char* title, int posX, int posY, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
	~Engine();
	bool Initialize(const char* title, int posX, int posY, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
	void HandleEvents();
	void Run();
	void Clean();
	bool GetRunningState() const;
	void SetRunningState(bool isRunning);

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Mix_Music* music;
	SDL_Texture* backgroundTxt;
	SDL_Texture* text;
	TextureManager* textureManager;
	TextManager* textMananger;
	AudioManager* audioManager;
	MainMenu* mainMenu;
	OptionsMenu* optionsMenu;
	InGame* inGame;
	TileManager* tileManager;
	Player player;

	const Uint8* keyState;

	void Update(float deltaTime);
	void Render();
};

#endif