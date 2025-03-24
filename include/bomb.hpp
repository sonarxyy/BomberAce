#ifndef BOMB_HPP
#define BOMB_HPP


#include <SDL.h>
#include <vector>
#include <string>
#include <algorithm>
#include "constants.hpp"
#include "tile_manager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "explosion.hpp"

class Player;
class Enemy;
class TileManager;
class Bomb {
public:
	enum class Entity {
		PLAYER,
		ENEMY
	} ownerType;

	Bomb(int px, int py, SDL_Renderer* renderer, TileManager& map, const Entity& owner);
	void LoadTexture(SDL_Renderer* renderer);
	void Update(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
	bool IsExploded() const { return !active; }
	SDL_Rect GetRect() const;
	int GetExplosionRadius() const;
	int GetExplosionId() const;
	Entity GetOwnerType() const;
	std::vector<std::pair<int, int>> pendingDestroyedTiles;
	std::vector<Enemy*> enemyKilled;

private:
	int x, y;
	Uint32 timer; // Time before explosion (milliseconds)
	Uint32 startTime, currentTime;
	bool active;
	TextureManager* textureManager;
	std::vector<SDL_Texture*> bombTextures;
	static std::vector<SDL_Texture*> sharedBombTextures; // Reuse bomb textures if already initialized
	void Explode(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer);
	bool CheckCollision(SDL_Rect explosionArea, SDL_Rect object);

	// Default power of the bomb
	int explosionRadius;

	// For bomb placement animation
	int currentFrame;
	Uint32 lastFrameTime;
	Uint32 frameDelay;

	bool playerOnBomb = true;
	bool enemyOnBomb = true;

	// For score calculation
	static int nextExplosionId;
	int explosionId;
};


#endif