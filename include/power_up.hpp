#ifndef POWERUP_HPP
#define POWERUP_HPp

#include <SDL.h>
#include "constants.hpp"

enum PowerUpType {
    BOMB_RANGE,
    FLAMETHROWER,
    LASER_GUN,
    SPEED,
    SHIELD,
    EXTRA_BOMBS
};

class PowerUp {
public:
    PowerUp(int x, int y, PowerUpType type);

    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
    PowerUpType getType() const;

private:
    int x, y;
    PowerUpType type;
    SDL_Rect rect;
};

#endif
