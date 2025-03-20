#ifndef BOMB_HPP
#define BOMB_HPP


#include <SDL.h>
#include <vector>
#include "tile_manager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "explosion.hpp"

class Player;
class Enemy; // Forward declaration to avoid compiler complaints

class Bomb {
public:
	Bomb(int px, int py);
	void Update(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
	bool IsExploded() const { return !active; }
	SDL_Rect GetRect() const;

private:
	int x, y;
	Uint32 timer; // Time before explosion (milliseconds)
	Uint32 startTime;
	bool active;
	void Explode(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer);
	bool CheckCollision(SDL_Rect explosionArea, SDL_Rect object);
};


#endif