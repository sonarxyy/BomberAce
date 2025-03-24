#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SDL.h>
#include <vector>
#include <string>
#include "constants.hpp"
#include "texture_manager.hpp"
#include "audio_manager.hpp"
#include <iomanip>
#include <sstream>

class Explosion {
public:
    Explosion(int x, int y, SDL_Renderer* renderer, const int& explosionId);
    void Update();
    void Render(SDL_Renderer* renderer);
    bool IsExpired() const;
    void LoadTexture(SDL_Renderer* renderer);
    std::vector<SDL_Rect> GetAffectedTiles();
    int GetExplosionId() const;

private:
    int x, y;
    int frameIndex;
    Uint32 lastFrameTime;
    SDL_Rect explosionRect;
    bool isExpired;
    std::vector<SDL_Texture*> frames;
    TextureManager* textureManager;
    static std::vector<SDL_Texture*> sharedFrames; // Reuse animation texture if already initialized
    AudioManager* audioManager;

    // For score calculation
    std::vector<SDL_Rect> affectedTiles;
    int explosionId;  // ID from the bomb that created this explosion
};

#endif
