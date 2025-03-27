#include "in_game.hpp"

InGame::InGame(SDL_Renderer* renderer)
    : renderer(renderer), levelManager(LEVEL_FOLDER) { // Initialize LevelManager
    textManager = new TextManager(renderer);
    textureManager = new TextureManager(renderer);
    audioManager = new AudioManager();

    tileManager = new TileManager(renderer, levelManager);
    level = 1;
    score = 0;
    hud = new HUD(renderer);
    player = new Player(renderer, *tileManager);

    // Initialize enemies
    enemies.push_back(Enemy(864, 48, renderer, 0));
    enemies.push_back(Enemy(48, 864, renderer, 1));
    enemies.push_back(Enemy(864, 864, renderer, 2));

    startTime = SDL_GetTicks();
    levelDuration = 150000;
}

InGame::~InGame() {
    delete textManager;
    delete textureManager;
    delete audioManager;
    delete tileManager;
    delete player;
    delete hud;
}

void InGame::HandleInputs(const Uint8* keyState) {
    if (player->GetHealth() > 0) {
        player->HandleInput(keyState, *tileManager, bombs);
    }
    // Handle input events here (e.g., keyboard input).
}

void InGame::Update() {
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    Uint32 remainingTime = (levelDuration > elapsedTime) ? (levelDuration - elapsedTime) : 0;

    if (player->GetHealth() == 0 && remainingTime == 0) {
        return; // Stop updating game objects if the player is dead or time reach 0;
    }

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

    if (enemies.empty()) {
        NextLevel();
    }
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

void InGame::NextLevel() {
    FadeTransition::fade(renderer, false);
    level++;
    score = 0;

    levelManager.NextLevel();

    tileManager->LoadLevel(levelManager);

    startTime = SDL_GetTicks();
    bombs.clear();
    explosions.clear();

    player->Reset();

    enemies.clear();
    enemies.push_back(Enemy(864, 48, renderer, 0));
    enemies.push_back(Enemy(48, 864, renderer, 1));
    enemies.push_back(Enemy(864, 864, renderer, 2));

    FadeTransition::fade(renderer, true);
}