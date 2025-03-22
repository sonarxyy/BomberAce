#include "in_game.hpp"

InGame::InGame(SDL_Renderer* renderer) : renderer(renderer) {
    player = new Player(renderer);
    level = 1;
    score = 0;
    textManager = new TextManager(renderer);
    textureManager = new TextureManager(renderer);
    audioManager = new AudioManager();
    tileManager = new TileManager(renderer);
    hud = new HUD(renderer);
    enemies.push_back(Enemy (816, 48, renderer));
    startTime = SDL_GetTicks();
    levelDuration = 150000;
}

InGame::~InGame() {
    delete textManager;
    delete textureManager;
    delete audioManager;
}

void InGame::HandleInputs(const Uint8* keyState) {
    player->HandleInput(keyState, *tileManager, bombs);
    // Handle input events here (e.g., keyboard input).
}

void InGame::Update() {
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    Uint32 remainingTime = (levelDuration > elapsedTime) ? (levelDuration - elapsedTime) : 0;
    for (auto& enemy : enemies) {
        enemy.Update(*tileManager, bombs, renderer);
    }

    for (auto& bomb : bombs) {
        bomb.Update(*tileManager, *player, enemies, explosions, renderer);
    }

    for (auto& explosion : explosions) {
        explosion.Update();
    }

    bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Bomb& b) { return b.IsExploded(); }), bombs.end());
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& e) { return !e.IsAlive(); }), enemies.end());
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](Explosion& ex) { return ex.IsExpired(); }), explosions.end());

    hud->Update(level, score, remainingTime, player->GetHealth());
}

void InGame::Render() {
    tileManager->Render(renderer);
    player->Render(renderer); // Render player

    for (auto& enemy : enemies) {
        enemy.Render(renderer); // Render enemies
    }

    for (auto& bomb : bombs) {
        bomb.Render(renderer); // Render bombs
    }

    for (auto& explosion : explosions) {
        explosion.Render(renderer); // Render explosion
    }
    hud->Render();
}