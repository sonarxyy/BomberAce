#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <map>

class TextureManager {
public:
	TextureManager();
	~TextureManager();
	static SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer);
	static void UnloadTexture(const char* path);
	void Clean();

private:
	static std::map<const char*, SDL_Texture*> textures; // Storing texture
};

#endif
