#include <texture_manager.hpp>

TextureManager::TextureManager(SDL_Renderer* renderer) : renderer(renderer) {
	// TODO: Other initializations
}

TextureManager::~TextureManager() {
	Clean();
}

SDL_Texture* TextureManager::LoadTexture(const char* path) {
	if (textures.find(path) != textures.end()) { // If texture is loaded
		return textures[path];
	}

	SDL_Texture* texture = IMG_LoadTexture(renderer, path);
	if (texture == nullptr) { 
		SDL_Log("Error loading texture %s", path);
		return nullptr;
	}

	textures[path] = texture; // Save imported texture
	return texture;
}

void TextureManager::UnloadTexture(const char* path) {
	auto it = textures.find(path);
	if (it != textures.end()) {
		SDL_DestroyTexture(it->second);
		textures.erase(it);
	}
}

void TextureManager::Clean() {
	for (auto& pair : textures) {
		SDL_DestroyTexture(pair.second);
	}
	textures.clear();
}

