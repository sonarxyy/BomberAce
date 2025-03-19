#ifndef BOMB_HPP
#define BOMB_HPP


#include <SDL.h>
#include <vector>
#include "tile_manager.hpp"

class Bomb {
public:
	Bomb(int px, int py);
	void Update(TileManager& map);
	void Render(SDL_Renderer* renderer);
	bool IsExploded() const { return !active; }
	SDL_Rect GetRect() const;

private:
	int x, y;
	Uint32 timer; // Time before explosion (milliseconds)
	Uint32 startTime;
	bool active;
	void Explode(TileManager& map);
};


#endif