#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SDL.h>
#include <constants.hpp>
#include <texture_manager.hpp>

class GameObject {
public:
	GameObject(const char* path, SDL_Renderer* renderer, int x, int y);
	virtual ~GameObject(); // Generic destructor for any game object
	void Update(float deltaTime);
	void Render();

protected: // So that derived class can have access to
	int xPos;
	int yPos;
	int width;
	int height;

private:
	TextureManager* textureManager;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, dstRect;
	SDL_Renderer* objRenderer;
};

#endif
