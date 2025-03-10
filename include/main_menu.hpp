#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SDL.h>
#include <cmath>
#include "constants.hpp"
#include "text_manager.hpp"
#include "texture_manager.hpp"
#include "audio_manager.hpp"
#include "game_states_manager.hpp"

class MainMenu {
public:
    MainMenu(SDL_Renderer* renderer);
    ~MainMenu();
    void CreateDisplay();
    void HandleInput(SDL_Event& event);
    void UpdateSelectorPosition();
    void UpdateTransition();
    void Render();

private:
    int screenWidth, screenHeight;
    
    // For animation
    int animationTimer, animationSpeed;
    bool isAnimating;

    TTF_Font* font;
    SDL_Texture* mainMenuBackground;

    SDL_Texture* gameTitleTexture;
    SDL_Rect gameTitleRect;

    SDL_Texture* menuBoxTexture;
    SDL_Rect menuBoxRect;

    SDL_Texture* startTexture;
    SDL_Rect startRect;

    SDL_Texture* optionsTexture;
    SDL_Rect optionsRect;

    SDL_Texture* quitTexture;
    SDL_Rect quitRect;

    SDL_Texture* selectorTexture;
    SDL_Rect selectorRect;

    SDL_Texture* selectedStartTexture;
    SDL_Texture* selectedOptionsTexture;
    SDL_Texture* selectedQuitTexture;

    Mix_Chunk* selectorSFX;
    Mix_Chunk* selectedSFX;

    // for selector
    enum MenuOption {
        Start,
        Options,
        Quit
    };
    MenuOption selectedOption;

    // For transition
    int gameTitleTargetX;
    int optionsTargetX;
    int quitTargetX;
    int startTargetX;
    int transitionSpeedGameTitle;
    int transitionSpeedOptions;
    int transitionSpeedQuit;
    int transitionSpeedStart;
    bool transitioningIn;

    TextManager* textManager;
    TextureManager* textureManager;
    AudioManager* audioManager;
    SDL_Renderer* renderer;
    SDL_Rect cursorRect;
};

#endif
