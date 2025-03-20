#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SDL.h>
#include <vector>
#include <string>
#include "constants.hpp"
#include "texture_manager.hpp"
#include <iomanip>
#include <sstream>

class Explosion {
public:
    Explosion(int x, int y, SDL_Renderer* renderer);
    void Update();
    void Render(SDL_Renderer* renderer);
    bool IsExpired() const;
    void LoadTexture(SDL_Renderer* renderer);

private:
    int x, y;
    int frameIndex;
    Uint32 lastFrameTime;
    SDL_Rect explosionRect;
    bool isExpired;
    std::vector<SDL_Texture*> frames;
    TextureManager* textureManager;
    static std::vector<SDL_Texture*> sharedFrames;
};

#endif
