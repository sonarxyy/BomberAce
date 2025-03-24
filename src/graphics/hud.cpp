#include "hud.hpp"

HUD::HUD(SDL_Renderer* renderer) : renderer(renderer), levelTexture(nullptr), scoreTexture(nullptr), timeTexture(nullptr) {
    textManager = new TextManager(renderer);
    textureManager = new TextureManager(renderer);
    heartTexture = textureManager->LoadTexture("assets/image/heart.png");
    font = textManager->LoadFont(OPEN_SANS_FONT_FILE, 25);
}


HUD::~HUD() {
    delete textManager;
    delete textureManager;
}

void HUD::Update(const int& level, const int& score, Uint32 remainingTime, const int& health) {
    SDL_DestroyTexture(levelTexture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(timeTexture);

    levelTexture = textManager->CreateTextureFromText(font, "Level: " + std::to_string(level), WHITE);
    SDL_QueryTexture(levelTexture, NULL, NULL, &tempW, &tempH);
    levelRect = { 192 - tempW / 2, 15, tempW, tempH };

    scoreTexture = textManager->CreateTextureFromText(font, "Score: " + std::to_string(score), WHITE);
    SDL_QueryTexture(scoreTexture, NULL, NULL, &tempW, &tempH);
    scoreRect = { SCREEN_WIDTH / 2 - tempW / 2, 15, tempW, tempH };

    timeTexture = textManager->CreateTextureFromText(font, "Time: " + std::to_string(remainingTime / 1000) + "s", WHITE);
    SDL_QueryTexture(timeTexture, NULL, NULL, &tempW, &tempH);
    timeRect = { SCREEN_WIDTH - 192 - tempW / 2, 15, tempW, tempH };

    heartTextures.clear();
    heartRects.clear();
    for (int i = 0; i < health; i++) {
        heartTextures.push_back(heartTexture);
        heartRects.push_back({ i * TILE_SIZE, TILE_SIZE / 8, TILE_SIZE * 3 / 2, TILE_SIZE * 3 / 2 });
    }
}

void HUD::Render() {
    SDL_RenderCopy(renderer, levelTexture, nullptr, &levelRect);
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    SDL_RenderCopy(renderer, timeTexture, nullptr, &timeRect);

    for (size_t i = 0; i < heartTextures.size(); i++) {
        SDL_RenderCopy(renderer, heartTextures[i], NULL, &heartRects[i]);
    }
}

