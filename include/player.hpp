#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>
#include "tile_manager.hpp"
#include "bomb.hpp"
#include <vector>

class Bomb;

class Player {
private:
	int x, y, width, height;
	int speed;
	int health;

public:
	Player();
	void HandleInput(SDL_Event& event, TileManager& map, std::vector<Bomb>& bombs);
	void Render(SDL_Renderer* renderer);
	SDL_Rect GetRect() const;
	int GetHealth() const;
	void TakeDamage();
	void SetPosition(int newX, int newY);
	void PlaceBomb(std::vector<Bomb>& bombs);
};

#endif