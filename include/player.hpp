#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "tile_manager.hpp"
#include "bomb.hpp"
#include "text_manager.hpp"
#include "texture_manager.hpp"
#include "audio_manager.hpp"
#include "constants.hpp"
#include <SDL_mixer.h>
#include <vector>
#include <iostream>

class Bomb;
class TileManager;

class Player {
private:
	int x, y, width, height;
	int speed;
	int health;
	int currentBombs;
	int maxBombs;
	int explosionRadius;

	// For SFX
	AudioManager* audioManager;
	Mix_Chunk* grassFootstep;
	Mix_Chunk* snowFootstep;
	Uint32 lastPlayTime, currentTime;

	// For animation
	TextureManager* textureManager;
	SDL_Renderer* renderer;
	SDL_Texture* playerTexture;

	SDL_Rect srcRect, destRect;
	int frame;
	Uint32 frameTime;
	Uint32 lastFrameTime;
	enum class State { IDLE, WALKING } state;
	enum class Direction { FRONT, BACK, LEFT, RIGHT } direction;

	// Game over
	SDL_Texture* gameoverBackground;
	TTF_Font* font;
	TextManager* textManager;
	

public:
	Player(SDL_Renderer* renderer, TileManager& map);
	~Player();
	void HandleInput(const Uint8* keyState, TileManager& map, std::vector<Bomb>& bombs);
	void UpdateAnimation();
	void Render(SDL_Renderer* renderer);
	SDL_Rect GetRect() const;
	int GetHealth() const;
	void TakeDamage();
	void SetPosition(int newX, int newY);
	void PlaceBomb(std::vector<Bomb>& bombs, TileManager& map);
	void GameOver();
	void OnBombExploded();
	void Reset();
	void CollectPowerUp(TileManager& map);
	int GetExplosionRadius() const;
	void SetHealth(int health);
};

#endif