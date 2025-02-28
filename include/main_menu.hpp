#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SDL.h>
#include <constants.hpp>
#include <text_manager.hpp>
#include <texture_manager.hpp>
#include <audio_manager.hpp>

class MainMenu {
public:
    MainMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~MainMenu();
    void CreateDisplay();
    void HandleInput(SDL_Event& event);
    void UpdateSelectorPosition();
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
    SDL_Texture* selectorTexture;
    SDL_Rect selectorRect;
    Mix_Chunk* selectorSFX;
    Mix_Chunk* selectedSFX;

    // for selector
    enum MenuOption {
        Start,
        Options,
        Quit
    };
    MenuOption selectedOption;
    TextManager* textManager;
    TextureManager* textureManager;
    AudioManager* audioManager;
    SDL_Renderer* renderer;
};

#endif
