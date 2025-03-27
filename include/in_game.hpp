#ifndef IN_GAME_HPP
#define IN_GAME_HPP

#include <SDL.h>
#include <unordered_set>
#include <algorithm>
#include "constants.hpp"
#include "game_states_manager.hpp"
#include "texture_manager.hpp"
#include "text_manager.hpp"
#include "audio_manager.hpp"
#include "tile_manager.hpp"
#include "level_manager.hpp"
#include "fade_transition.hpp";
#include "player.hpp"
#include "bomb.hpp"
#include "enemy.hpp"
#include "explosion.hpp"
#include "hud.hpp"
#include "power_up.hpp"

class InGame {
public:
	InGame(SDL_Renderer* renderer);
	~InGame();
	void HandleInputs(const Uint8* keyState);
	void Update();
	void Render();
	void NextLevel();

private:
	SDL_Renderer* renderer;
	TextManager* textManager;
	TextureManager* textureManager;
	AudioManager* audioManager;
	TileManager* tileManager;
	LevelManager levelManager;

	Player* player;
	std::vector<Bomb> bombs;
	std::vector<Enemy> enemies;
	std::vector<Explosion> explosions;
	HUD* hud;

	int level;
	int score;
	Uint32 startTime;
	Uint32 levelDuration;
};

#endif