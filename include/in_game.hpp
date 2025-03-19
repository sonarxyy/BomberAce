#ifndef IN_GAME_HPP
#define IN_GAME_HPP

#include <SDL.h>
#include "constants.hpp"
#include "game_states_manager.hpp"
#include "texture_manager.hpp"
#include "text_manager.hpp"
#include "audio_manager.hpp"
#include "tile_manager.hpp"
#include "player.hpp"
#include "bomb.hpp"
#include "enemy.hpp"

class InGame {
public:
	InGame(SDL_Renderer* renderer);
	~InGame();
	void HandleInputs(SDL_Event& event);
	void Update();
	void Render();


private:
	SDL_Renderer* renderer;
	TextManager* textManager;
	TextureManager* textureManager;
	AudioManager* audioManager;
	TileManager* tileManager;
	Player player;
	std::vector<Bomb> bombs;
	std::vector<Enemy> enemies;
};

#endif