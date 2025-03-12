#include "in_game.hpp"

InGame::InGame(SDL_Renderer* renderer) : renderer(renderer) {
    textManager = new TextManager(renderer);
    textureManager = new TextureManager(renderer);
    audioManager = new AudioManager();
    backgroundDesertX = 0;
    CreateDisplay();
}

InGame::~InGame() {
    delete textManager;
    delete textureManager;
    delete audioManager;
}

void InGame::CreateDisplay() {
    backgroundDesert = textureManager->LoadTexture(BACKGROUND_DESERT_FILE);
    SDL_QueryTexture(backgroundDesert, NULL, NULL, &backgroundDesertWidth, &backgroundDesertHeight);

    // Render the background twice to create an infinite scrolling effect.
    backgroundDesertDestRect1 = { backgroundDesertX, 0, backgroundDesertWidth, backgroundDesertHeight };
    backgroundDesertDestRect2 = { backgroundDesertX + backgroundDesertWidth, 0, backgroundDesertWidth, backgroundDesertHeight };
}

void InGame::HandleInputs(SDL_Event& event) {

}

void InGame::Update() {
    // Scroll the background to the left.
    backgroundDesertX -= 50; // Adjust the scrolling speed as needed.

    // If the background has scrolled off the screen, reset its position.
    if (backgroundDesertX < -backgroundDesertWidth) {
        backgroundDesertX = 0;
    }
}

void InGame::Render() {
    SDL_RenderCopy(renderer, backgroundDesert, NULL, &backgroundDesertDestRect1);
    SDL_RenderCopy(renderer, backgroundDesert, NULL, &backgroundDesertDestRect2);
}