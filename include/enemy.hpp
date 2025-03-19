#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL.h>
#include "tile_manager.hpp"
#include "player.hpp"
#include "bomb.hpp"
#include <vector>

class Enemy {
public:
    Enemy(int startX, int startY);
    void Update(TileManager& map, Player& player, std::vector<Bomb>& bombs);
    void Render(SDL_Renderer* renderer);
    void Kill();
    bool IsAlive() const { return alive; }
    SDL_Rect GetRect() const;

private:
    int x, y;
    int speed;
    int width, height;
    bool alive;
    int direction; // 0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
    int moveTimer; // Change direction every few frames

    void ChooseDirection(TileManager& map, Player& player, std::vector<Bomb>& bombs);
};

#endif
