#include "options_menu.hpp"


OptionsMenu::OptionsMenu(SDL_Renderer* renderer) : renderer(renderer), screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), font(nullptr) {
    textManager = new TextManager(renderer);
    textureManager = new TextureManager(renderer);
    audioManager = new AudioManager();
    CreateDisplay();
}

OptionsMenu::~OptionsMenu() {
    delete textureManager;
    delete textManager;
    delete audioManager;
}

void OptionsMenu::CreateDisplay() {
    font = textManager->LoadFont(FONT_FILE, 20);
    optionsMenuBackground = textureManager->LoadTexture(OPTIONSMENU_BACKGROUND);

    // fullScreenTexture = textManager->CreateTextureFromText(font, "Full Screen", WHITE);
    // SDL_QueryTexture(fullScreenTexture, NULL, NULL, &fullScreenRect.w, &fullScreenRect.h);
}

void OptionsMenu::HandleInputs(SDL_Event& event) {
    
}

void OptionsMenu::Update() {

}

void OptionsMenu::Render() {
    SDL_RenderCopy(renderer, optionsMenuBackground, NULL, NULL);
    // SDL_RenderCopy(renderer, fullScreenTexture, NULL, &fullScreenRect);
}