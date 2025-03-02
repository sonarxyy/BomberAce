#ifndef TEXT_MANAGER_HPP
#define TEXT_MANAGER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>

class TextManager {
public:
    TextManager(SDL_Renderer* renderer);
    ~TextManager();

    TTF_Font* LoadFont(const char* fontPath, int fontSize);
    SDL_Texture* CreateTextureFromText(TTF_Font* font, const char* text, SDL_Color color);
    void UnloadFont(TTF_Font* font);
    void UnloadTexture(SDL_Texture* texture);
    void Clean(); // Unload all fonts and textures

private:
    SDL_Renderer* renderer;
    int textWidth, textHeight;
    std::map<std::pair<const char*, int>, TTF_Font*> fonts; // Store font path, size
    std::vector<SDL_Texture*> textures; // Store created textures for cleanup
};

#endif