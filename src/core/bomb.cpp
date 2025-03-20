#include "bomb.hpp"
#include <iostream>

Bomb::Bomb(int px, int py) {
    x = (px / TILE_SIZE) * TILE_SIZE; // Align to grid
    y = (py / TILE_SIZE) * TILE_SIZE;
    timer = 3000; // 3 seconds before explosion
    startTime = SDL_GetTicks();
    active = true;
}

void Bomb::Update(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer) {
    if (!active) return;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - startTime >= timer) {
        active = false;
        Explode(map, player, enemies, explosions, renderer);
    }
}

void Bomb::Explode(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer) {
    int gridX = x / TILE_SIZE;
    int gridY = y / TILE_SIZE;
    int explosionRange = 1;

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
    for (int i = 1; i <= explosionRange; i++) {
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

    SDL_Rect rect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Bomb::GetRect() const {
    return { x, y };
}

bool Bomb::CheckCollision(SDL_Rect explosionArea, SDL_Rect object) {
    return SDL_HasIntersection(&explosionArea, &object);
}