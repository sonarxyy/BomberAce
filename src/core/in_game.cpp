#include "in_game.hpp"

InGame::InGame(SDL_Renderer* renderer) : renderer(renderer) {
    textManager = new TextManager(renderer);
    textureManager = new TextureManager(renderer);
    audioManager = new AudioManager();
    tileManager = new TileManager(renderer);
    player = new Player(renderer, *tileManager);
    level = 1;
    score = 0;
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
    if (player->GetHealth() > 0) {
        player->HandleInput(keyState, *tileManager, bombs);
    }
    // Handle input events here (e.g., keyboard input).
}

void InGame::Update() {
    if (player->GetHealth() == 0) {
        return; // Stop updating game objects if the player is dead
    }

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

        for (const auto& pos : explosion.GetAffectedTiles()) {
            int col = pos.x / TILE_SIZE;
            int row = pos.y / TILE_SIZE;

            if (!tileManager->IsWall(col, row)) {
                TileManager::TileType tileType = tileManager->GetTileTypeAt(pos.x, pos.y);

                if (tileType == TileManager::TileType::BREAKABLE) {
                    for (const auto& bomb : bombs) {
                        if (bomb.GetExplosionId() == explosion.GetExplosionId()) {
                            if (bomb.GetOwnerType() == Bomb::Entity::PLAYER) {
                                score += 10;  // Add score for destroying a breakable tile
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto& bomb : bombs) {
        if (bomb.GetOwnerType() == Bomb::Entity::PLAYER) {
            std::unordered_set<Enemy*> countedEnemies;
            for (auto& enemy : bomb.enemyKilled) {
                if (countedEnemies.find(enemy) == countedEnemies.end()) {
                    score += 100;  // Add 100 points per enemy kill
                    countedEnemies.insert(enemy);
                }
            }
        }
    }

    // Handle tile destruction and enemy removal after all explosions are processed
    for (auto& bomb : bombs) {
        for (const auto& tile : bomb.pendingDestroyedTiles) {
            tileManager->DestroyTile(tile.first, tile.second);
        }
        bomb.pendingDestroyedTiles.clear(); // Clear the list after processing

        for (auto& enemy : bomb.enemyKilled) {
            enemy->Kill();
        }
        bomb.enemyKilled.clear();
    }

    // Clean up exploded bombs, dead enemies, and expired explosions
    bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Bomb& b) { return b.IsExploded(); }), bombs.end());
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& e) { return !e.IsAlive(); }), enemies.end());
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](Explosion& ex) { return ex.IsExpired(); }), explosions.end());

    hud->Update(level, score, remainingTime, player->GetHealth());
}

void InGame::Render() {
    tileManager->Render(renderer);

    if (player->GetHealth() == 0) {
        player->GameOver();
        return;
    }
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