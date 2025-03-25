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
    std::vector<Enemy*> enemies;
    Enemy(int startX, int startY, SDL_Renderer* renderer, int enemyIndex);
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
    
    // For animation
    TextureManager* textureManager;
    SDL_Texture* texture;

    SDL_Rect srcRect, destRect;
    int frame;
    Uint32 frameTime;
    Uint32 lastFrameTime;
    enum class State { IDLE, WALKING } state;
    enum class Direction { BACK, FRONT, LEFT, RIGHT } direction;

    int moveTimer; // Change direction every few frames
    int bombCooldown;

    Uint32 lastRetryTime;
    bool IsInBombRadius(int x, int y, std::vector<Bomb>& bombs);
    void ChooseDirection(TileManager& map, std::vector<Bomb>& bombs);
    void EscapeFromBomb(TileManager& map, std::vector<Bomb>& bombs);
    void UpdateAnimation();
};

#endif
