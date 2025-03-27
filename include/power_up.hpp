#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SDL.h>
#include "constants.hpp"

enum PowerUpType {
    BOMB_RANGE,
    SPEED,
    SHIELD,
    EXTRA_BOMBS
};

class PowerUp {
public:
    PowerUp(int x, int y, PowerUpType type);

    void Render(SDL_Renderer* renderer);
    SDL_Rect GetRect() const;
    PowerUpType GetType() const;
private:
    int x, y;
    PowerUpType type;
    SDL_Rect rect;
};

#endif
