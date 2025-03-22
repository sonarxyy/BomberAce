#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL.h>
#include "tile_manager.hpp"
#include "player.hpp"
#include "bomb.hpp"
#include <vector>

class Bomb;
class Player;
class TileManager;

class Enemy {
public:
    Enemy(int startX, int startY, SDL_Renderer* renderer);
    void Update(TileManager& map, std::vector<Bomb>& bombs, SDL_Renderer* renderer);
    void PlaceBomb(std::vector<Bomb>& bombs, SDL_Renderer* renderer, TileManager& map);
    void Render(SDL_Renderer* renderer);
    void Kill();
    bool IsAlive() const { return alive; }
    SDL_Rect GetRect() const;

private:
    int x, y;
    int speed;
    int width, height;
    bool alive;
    SDL_Renderer* renderer;
    int direction; // 0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
    int moveTimer; // Change direction every few frames
    int bombCooldown;

    Uint32 lastRetryTime;
    bool IsInBombRadius(int x, int y, std::vector<Bomb>& bombs);
    void ChooseDirection(TileManager& map, std::vector<Bomb>& bombs);
    void EscapeFromBomb(TileManager& map, std::vector<Bomb>& bombs);
};

#endif
