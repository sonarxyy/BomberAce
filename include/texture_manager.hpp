#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <map>

class TextureManager {
public:
	TextureManager(SDL_Renderer* renderer);
	~TextureManager();
	SDL_Texture* LoadTexture(const char* path);
	void UnloadTexture(const char* path);
	void Clean();

private:
	SDL_Renderer* renderer;
	std::map<const char*, SDL_Texture*> textures; // Storing texture
};

#endif
