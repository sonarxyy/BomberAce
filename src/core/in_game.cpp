#include "in_game.hpp"

InGame::InGame(SDL_Renderer* renderer) : renderer(renderer) {
    textManager = new TextManager(renderer);
    textureManager = new TextureManager(renderer);
    audioManager = new AudioManager();
    tileManager = new TileManager(renderer);
}

InGame::~InGame() {
    delete textManager;
    delete textureManager;
    delete audioManager;
}

void InGame::HandleInputs(SDL_Event& event) {
    player.HandleInput(event);
    // Handle input events here (e.g., keyboard input).
}

void InGame::Update() {
    /*for (auto& enemy : enemies) {
        enemy.Update(*tileManager, player, bombs);
    }

    for (auto& bomb : bombs) {
        bomb.Update(*tileManager);
    }

    bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Bomb& b) { return b.IsExploded(); }), bombs.end());
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& e) { return !e.IsAlive(); }), enemies.end());*/
}

void InGame::Render() {
    tileManager->Render(renderer);
    player.Render(renderer); // Render player

    //for (auto& enemy : enemies) {
    //    enemy.Render(renderer); // Render enemies
    //}

    //for (auto& bomb : bombs) {
    //    bomb.Render(renderer); // Render bombs
    //}
}