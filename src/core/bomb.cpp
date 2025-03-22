#include "bomb.hpp"

std::vector<SDL_Texture*> Bomb::sharedBombTextures;
Bomb::Bomb(int px, int py, SDL_Renderer* renderer) {
    textureManager = new TextureManager(renderer);
    x = (px / TILE_SIZE) * TILE_SIZE; // Align to grid
    y = (py / TILE_SIZE) * TILE_SIZE;
    timer = 3000; // 3 seconds before explosion
    frameDelay = 90; // For bomb animation
    startTime = SDL_GetTicks();
    lastFrameTime = SDL_GetTicks();
    active = true;
    currentFrame = 0;
    explosionRadius = 1;
    LoadTexture(renderer);
}

void Bomb::LoadTexture(SDL_Renderer* renderer) {
    if (!sharedBombTextures.empty()) {
        bombTextures = sharedBombTextures;
        return;
    }
    else {
        for (int i = 0; i < BOMB_FRAME; i++) {
            std::string path = "assets/animations/bomb/bomb" + std::to_string(i) + ".png";
            sharedBombTextures.push_back(textureManager->LoadTexture(path.c_str()));
        }
    }
    bombTextures = sharedBombTextures;
}

void Bomb::Update(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer) {
    if (!active) return;

    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastFrameTime >= frameDelay) {
        currentFrame = (currentFrame + 1) % BOMB_FRAME;
        lastFrameTime = currentTime;
    }

    if (currentTime - startTime >= timer) {
        active = false;
        Explode(map, player, enemies, explosions, renderer);
    }
}

void Bomb::Explode(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer) {
    int gridX = x / TILE_SIZE;
    int gridY = y / TILE_SIZE;

    // Create explosion center
    explosions.push_back(Explosion(x, y, renderer));

    // Check collision at explosion center
    SDL_Rect explosionRect = { x, y, TILE_SIZE, TILE_SIZE };

    if (CheckCollision(explosionRect, player.GetRect())) {
        player.TakeDamage();
    }

    for (auto& enemy : enemies) {
        if (CheckCollision(explosionRect, enemy.GetRect())) {
            enemy.Kill();
        }
    }

    // Create explosion in 4 directions
    for (int i = 1; i <= explosionRadius; i++) {
        if (!map.DestroyTile(gridX + i, gridY)) {
            int ex = (gridX + i) * TILE_SIZE;
            int ey = gridY * TILE_SIZE;
            explosions.push_back(Explosion(ex, ey, renderer));
            explosionRect = { ex, ey, TILE_SIZE, TILE_SIZE };

            if (CheckCollision(explosionRect, player.GetRect())) {
                player.TakeDamage();
            }

            for (auto& enemy : enemies) {
                if (CheckCollision(explosionRect, enemy.GetRect())) {
                    enemy.Kill();
                }
            }
        }

        if (!map.DestroyTile(gridX - i, gridY)) {
            int ex = (gridX - i) * TILE_SIZE;
            int ey = gridY * TILE_SIZE;
            explosions.push_back(Explosion(ex, ey, renderer));
            explosionRect = { ex, ey, TILE_SIZE, TILE_SIZE };

            if (CheckCollision(explosionRect, player.GetRect())) {
                player.TakeDamage();
            }

            for (auto& enemy : enemies) {
                if (CheckCollision(explosionRect, enemy.GetRect())) {
                    enemy.Kill();
                }
            }
        }

        if (!map.DestroyTile(gridX, gridY + i)) {
            int ex = gridX * TILE_SIZE;
            int ey = (gridY + i) * TILE_SIZE;
            explosions.push_back(Explosion(ex, ey, renderer));
            explosionRect = { ex, ey, TILE_SIZE, TILE_SIZE };

            if (CheckCollision(explosionRect, player.GetRect())) {
                player.TakeDamage();
            }

            for (auto& enemy : enemies) {
                if (CheckCollision(explosionRect, enemy.GetRect())) {
                    enemy.Kill();
                }
            }
        }

        if (!map.DestroyTile(gridX, gridY - i)) {
            int ex = gridX * TILE_SIZE;
            int ey = (gridY - i) * TILE_SIZE;
            explosions.push_back(Explosion(ex, ey, renderer));
            explosionRect = { ex, ey, TILE_SIZE, TILE_SIZE };

            if (CheckCollision(explosionRect, player.GetRect())) {
                player.TakeDamage();
            }

            for (auto& enemy : enemies) {
                if (CheckCollision(explosionRect, enemy.GetRect())) {
                    enemy.Kill();
                }
            }
        }
    }
}

void Bomb::Render(SDL_Renderer* renderer) {
    if (!active) return;

    SDL_Rect rect = { x - TILE_SIZE / 8, y - TILE_SIZE / 4, 64, 64 };
    
    SDL_RenderCopy(renderer, bombTextures[currentFrame], NULL, &rect);
}

SDL_Rect Bomb::GetRect() const {
    return { x, y };
}

bool Bomb::CheckCollision(SDL_Rect explosionArea, SDL_Rect object) {
    return SDL_HasIntersection(&explosionArea, &object);
}

int Bomb::GetExplosionRadius() const {
    return explosionRadius;
}
