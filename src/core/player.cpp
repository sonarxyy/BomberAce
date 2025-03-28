#include "player.hpp"

Player::Player(SDL_Renderer* renderer, TileManager& map) : renderer(renderer) {
    textureManager = new TextureManager(renderer);
    textManager = new TextManager(renderer);
    audioManager = new AudioManager();
    font = textManager->LoadFont(OPEN_SANS_FONT_FILE, 30);
    grassFootstep = audioManager->LoadSound(GRASS_FOOTSTEP_EFFECT);
    snowFootstep = audioManager->LoadSound(SNOW_FOOTSTEP_EFFECT);
    x = 48;
    y = 48;
    speed = TILE_SIZE / 12;
    width = TILE_SIZE;
    height = TILE_SIZE;
    explosionRadius = 1;
    srcRect = { x , y, width, height };
    destRect = { x , y, width, height };
    health = 3;
    currentBombs = 0;
    maxBombs = 1;
    
    playerTexture = IMG_LoadTexture(renderer, PLAYER_SPRITESHEET);
    gameoverBackground = IMG_LoadTexture(renderer, GAMEOVER_BACKGROUND);

    // SFX
    lastPlayTime = 0;
    currentTime = 0;

    // Animation
    frame = 0;
    frameTime = 120; // 120ms per frame
    lastFrameTime = 0;
    state = State::IDLE;
    direction = Direction::FRONT;
}

Player::~Player() {
    delete audioManager;
}

void Player::TakeDamage() {
    if (health > 0) {
        health--;
    }

    if (health == 0) {
        GameOver();
    }
}

void Player::HandleInput(const Uint8* keyState, TileManager& map, std::vector<Bomb>& bombs) {
    int oldX = x, oldY = y;
    int newX = x, newY = y;
    bool moved = false;

    // Handle movement input
    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]) {
        newY -= speed;
        direction = Direction::BACK;
    }
    if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]) {
        newY += speed;
        direction = Direction::FRONT;
    }
    if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
        newX -= speed;
        direction = Direction::LEFT;
    }
    if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
        newX += speed;
        direction = Direction::RIGHT;
    }
    if (keyState[SDL_SCANCODE_SPACE]) {
        PlaceBomb(bombs, map);
    }

    // Check for collisions before applying movement
    SDL_Rect newRect = { newX, newY, width, height };
    if (!map.CheckCollision(newRect)) {
        x = newX;
        y = newY;
    }

    // Determine if the player actually moved
    moved = (x != oldX || y != oldY);
    state = moved ? State::WALKING : State::IDLE;

    // Check if the player steps on a power-up
    int tileCol = x / TILE_SIZE;
    int tileRow = y / TILE_SIZE;

    if (map.GetTileTypeAt(x, y) == TileManager::TileType::POWER_UP) {
        CollectPowerUp(map);
    }

    // Play footstep sound only if moving into a new tile
    if (moved) {
        Uint32 currentTime = SDL_GetTicks();
        static int lastTileCol = tileCol, lastTileRow = tileRow;

        if ((tileCol != lastTileCol || tileRow != lastTileRow) && (currentTime - lastPlayTime > 200)) {
            TileManager::TileType tileType = map.GetTileTypeAt(x, y);

            switch (tileType) {
            case TileManager::TileType::GRASS:
                audioManager->PlaySound(grassFootstep);
                break;
            case TileManager::TileType::SNOW:
                audioManager->PlaySound(snowFootstep);
                break;
            }

            lastPlayTime = currentTime;
            lastTileCol = tileCol;
            lastTileRow = tileRow;
        }
    }
}


void Player::UpdateAnimation() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime > frameTime) {
        frame = (frame + 1) % 4;  // Cycle through 4 frames
        lastFrameTime = currentTime;
    }

    // Determine sprite position based on state and direction
    int row = 0;
    int startCol = 0;

    if (direction == Direction::FRONT) startCol = 0;
    if (direction == Direction::RIGHT) startCol = 8;
    if (direction == Direction::BACK) startCol = 16;
    if (direction == Direction::LEFT) startCol = 24;

    if (state == State::IDLE) row = 0;
    if (state == State::WALKING) row = 1;

    srcRect = { (startCol + frame) * SPRITE_TILE, row * SPRITE_TILE, SPRITE_TILE, SPRITE_TILE };
}

void Player::Render(SDL_Renderer* renderer) {
    UpdateAnimation();
    destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, playerTexture, &srcRect, &destRect);
}

SDL_Rect Player::GetRect() const {
    return { x, y , width, height};
}

int Player::GetHealth() const {
    return health;
}

void Player::SetPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::PlaceBomb(std::vector<Bomb>& bombs, TileManager& map) {
    if (currentBombs >= maxBombs) {
        return;  // Don't place a bomb if max is reached
    }

    int bombX = (x / TILE_SIZE) * TILE_SIZE;
    int bombY = (y / TILE_SIZE) * TILE_SIZE;

    // Ensure no bomb exists at this location
    for (const auto& bomb : bombs) {
        if (bomb.GetRect().x == bombX && bomb.GetRect().y == bombY) {
            return;  // Don't place bomb if one already exists in this position
        }
    }

    // Place the bomb and increase the counter
    bombs.emplace_back(bombX, bombY, renderer, map, Bomb::Entity::PLAYER, explosionRadius);
    currentBombs++;
}

void Player::GameOver() {
    SDL_RenderClear(renderer);

    // Render background
    SDL_RenderCopy(renderer, gameoverBackground, NULL, NULL);

    SDL_Texture* textTexture = textManager->CreateTextureFromText(font, "Press R to retry", WHITE);
    SDL_Rect textRect;
    int w, h;
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
    textRect.w = w;
    textRect.h = h;
    textRect.x = (SCREEN_WIDTH - textRect.w) / 2;  // Center horizontally
    textRect.y = SCREEN_HEIGHT - textRect.h - 50;   // Position at the bottom with some margin

    // Render text
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

void Player::OnBombExploded() {
    if (currentBombs > 0) {
        currentBombs--;  // Reduce bomb count when a bomb explodes
    }
}

void Player::Reset() {
    x = 48;
    y = 48;
    health = 3;
    currentBombs = 0;
    maxBombs = 1;
    explosionRadius = 1;
    state = State::IDLE;
    direction = Direction::FRONT;
}

void Player::CollectPowerUp(TileManager& map) {
    int tileX = x / TILE_SIZE;
    int tileY = y / TILE_SIZE;

    for (auto& powerUp : map.GetPowerUps()) {
        SDL_Rect powerUpRect = powerUp.GetRect();
        SDL_Rect playerRect = GetRect();
        if (SDL_HasIntersection(&powerUpRect, &playerRect)) {
            switch (powerUp.GetType()) {
            case BOMB_RANGE:
                explosionRadius++;
                break;
            case SPEED:
                if (speed < TILE_SIZE / 8) { speed += 2; } // Limit max speed
                break;
            case SHIELD:
                health = std::min(health + 1, 3); // Increase HP but cap at 3
                break;
            case EXTRA_BOMBS:
                maxBombs = std::min(maxBombs + 1, 3); // Increase bomb capacity but cap at 3
                break;
            }

            map.RemovePowerUpAt(tileX * TILE_SIZE, tileY * TILE_SIZE);
            break;
        }
    }
}

int Player::GetExplosionRadius() const { 
    return explosionRadius; 
}

void Player::SetHealth(int health) {
    this->health = health;
}

