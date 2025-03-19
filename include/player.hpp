#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>

class Player {
private:
	int x, y, width, height;
	int speed;

public:
	Player();
	void HandleInput(SDL_Event& event);
	void Render(SDL_Renderer* renderer);
	SDL_Rect GetRect() const;
};

#endif