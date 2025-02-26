#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <constants.hpp>
#include <text_manager.hpp>
#include <texture_manager.hpp>
#include <audio_manager.hpp>

class MainMenu {
public:
    MainMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~MainMenu();
    void CreateDisplay();
    void Render();

private:
    int screenWidth;
    int screenHeight;

    TTF_Font* font;
    SDL_Texture* mainMenuBackground;
    SDL_Texture* gameTitleTexture;
    SDL_Rect gameTitleRect;
    SDL_Texture* startTexture;
    SDL_Rect startRect;
    SDL_Texture* optionsTexture;
    SDL_Rect optionsRect;
    SDL_Texture* quitTexture;
    SDL_Rect quitRect;

    TextManager* textManager;
    TextureManager* textureManager;
    SDL_Renderer* renderer;
};

#endif
