#include "game_object.hpp"

GameObject::GameObject(const char* path, SDL_Renderer* renderer, int x, int y) : textureManager(new TextureManager(renderer)) {
	xPos = x;
	yPos = y;
}

GameObject::~GameObject() {
	
}

void GameObject::Update(float deltaTime) {
	// xPos++ * deltaTime;
	// yPos++ * deltaTime;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 80;
	srcRect.h = 80;

	dstRect.x = xPos;
	dstRect.y = yPos;
	dstRect.w = 64;
	dstRect.h = 64;
}

void GameObject::Render() {
	SDL_RenderCopy(objRenderer, objTexture, &srcRect, &dstRect);
}


