#include "explosion.hpp"

std::vector<SDL_Texture*> Explosion::sharedFrames;

Explosion::Explosion(int x, int y, SDL_Renderer* renderer, const int& explosionId) : x(x), y(y), frameIndex(0), isExpired(false), explosionId(explosionId) {
    textureManager = new TextureManager(renderer);
    audioManager = new AudioManager();
    audioManager->PlaySound(audioManager->LoadSound(EXPLOSION_EFFECT));
    lastFrameTime = SDL_GetTicks();
    explosionRect = { x, y , TILE_SIZE, TILE_SIZE};
    LoadTexture(renderer);
    affectedTiles.push_back(explosionRect);
}

void Explosion::LoadTexture(SDL_Renderer* renderer) {
    if (!sharedFrames.empty()) {  // If already loaded, reuse
        frames = sharedFrames;
        return;
    }

    for (int i = 0; i < EXPLOSION_FRAME; i++) {
        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << i;
        std::string path = "assets/effect/Effect_Explosion/Effect_Explosion_1_" + oss.str() + ".png";

        SDL_Texture* texture = textureManager->LoadTexture(path.c_str());
        sharedFrames.push_back(texture);
    }

    frames = sharedFrames;
}

void Explosion::Update() {
    if (isExpired) return;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime > 16) {
        lastFrameTime = currentTime;
        frameIndex++;

        if (frameIndex >= frames.size()) {
            isExpired = true;
        }
    }
}

void Explosion::Render(SDL_Renderer* renderer) {
    if (isExpired || frameIndex >= frames.size()) return;

    SDL_RenderCopy(renderer, frames[frameIndex], NULL, &explosionRect);
}

bool Explosion::IsExpired() const {
    return isExpired;
}

std::vector<SDL_Rect> Explosion::GetAffectedTiles() {
    return affectedTiles;
}

int Explosion::GetExplosionId() const {
    return explosionId;
}