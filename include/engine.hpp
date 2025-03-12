#ifndef ENGINE_HPP
#define ENGINE_HPP

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
#include "game_object.hpp"
#include "vector.hpp"

class Engine {
public:
	Engine(const char* title, int posX, int posY, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
	~Engine();
	bool Initialize(const char* title, int posX, int posY, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
	void HandleEvents();
	void Run();
	void Clean();
	bool getRunningState() const;

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Mix_Music* music;

	GameObject* playerObj;
	SDL_Texture* backgroundTxt;
	SDL_Texture* text;
	TextureManager* textureManager;
	TextManager* textMananger;
	AudioManager* audioManager;
	MainMenu* mainMenu;
	OptionsMenu* optionsMenu;
	InGame* inGame;

	void Update(float deltaTime);
	void Render();
};

#endif