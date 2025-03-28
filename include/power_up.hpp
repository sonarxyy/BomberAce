#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SDL.h>
#include "constants.hpp"
#include "texture_manager.hpp"

enum PowerUpType {
    BOMB_RANGE = 10,
    SPEED,
    SHIELD,
    EXTRA_BOMBS
};

class PowerUp {
public:
    PowerUp(int x, int y, PowerUpType type, SDL_Renderer* renderer);

    void Render(SDL_Renderer* renderer);
    SDL_Rect GetRect() const;
    PowerUpType GetType() const;
private:
    int x, y;
    PowerUpType type;
    SDL_Rect rect;
    
    SDL_Texture* bombRangeTexture;
    SDL_Texture* speedTexture;
    SDL_Texture* shieldTexture;
    SDL_Texture* extraBombTexture;
    TextureManager* textureManager;
    SDL_Renderer* renderer;
};

#endif
