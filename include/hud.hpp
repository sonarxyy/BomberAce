#ifndef HUD_HPP
#define HUD_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "text_manager.hpp"
#include "texture_manager.hpp"
#include "constants.hpp"

class HUD {
public:
    HUD(SDL_Renderer* renderer);
    ~HUD();

    void Update(const int& level, const int& score, Uint32 remainingTime, const int& health);
    void Render();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    int tempW, tempH;
    SDL_Texture* levelTexture;
    SDL_Texture* scoreTexture;
    SDL_Texture* timeTexture;
    SDL_Rect levelRect, scoreRect, timeRect;
    std::vector<SDL_Texture*> heartTextures;
    std::vector<SDL_Rect> heartRects;
    SDL_Texture* heartTexture;

    TextManager* textManager;
    TextureManager* textureManager;
};

#endif
