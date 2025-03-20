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
    font = textManager->LoadFont(OPEN_SANS_FONT_FILE, 20);
    optionsMenuBackground = textureManager->LoadTexture(OPTIONSMENU_BACKGROUND);

    // Full Screen Texture
    fullScreenTexture = textManager->CreateTextureFromText(font, "Full Screen", WHITE);
    SDL_QueryTexture(fullScreenTexture, NULL, NULL, &fullScreenRect.w, &fullScreenRect.h);
    fullScreenRect.x = SCREEN_WIDTH / 4;
    fullScreenRect.y = SCREEN_HEIGHT / 4;

    // Music Volume Texture
    musicVolumeTexture = textManager->CreateTextureFromText(font, "Music Volume", WHITE);
    SDL_QueryTexture(musicVolumeTexture, NULL, NULL, &musicVolumeRect.w, &musicVolumeRect.h);
    musicVolumeRect.x = SCREEN_WIDTH / 4;
    musicVolumeRect.y = fullScreenRect.y + fullScreenRect.h + 50;

    // SFX Volume Texture
    SFXVolumeTexture = textManager->CreateTextureFromText(font, "SFX Volume", WHITE);
    SDL_QueryTexture(SFXVolumeTexture, NULL, NULL, &SFXVolumeRect.w, &SFXVolumeRect.h);
    SFXVolumeRect.x = SCREEN_WIDTH / 4;
    SFXVolumeRect.y = musicVolumeRect.y + musicVolumeRect.h + 50;

}

void OptionsMenu::HandleInputs(SDL_Event& event) {
    
}

void OptionsMenu::Update() {

}

void OptionsMenu::Render() {
    SDL_RenderCopy(renderer, optionsMenuBackground, NULL, NULL);
    SDL_RenderCopy(renderer, fullScreenTexture, NULL, &fullScreenRect);
    SDL_RenderCopy(renderer, musicVolumeTexture, NULL, &musicVolumeRect);
    SDL_RenderCopy(renderer, SFXVolumeTexture, NULL, &SFXVolumeRect);
}