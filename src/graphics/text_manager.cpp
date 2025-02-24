#include "text_manager.hpp"

TextManager::TextManager(SDL_Renderer* renderer) : renderer(renderer) {
    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

TextManager::~TextManager() {
    Clean();
    TTF_Quit();
}

TTF_Font* TextManager::LoadFont(const char* fontPath, int fontSize) {
    std::pair<const char*, int> fontKey = std::make_pair(fontPath, fontSize);
    if (fonts.find(fontKey) != fonts.end()) {
        return fonts[fontKey]; // Font already loaded
    }

    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (font == nullptr) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return nullptr;
    }

    fonts[fontKey] = font;
    return font;
}

SDL_Texture* TextManager::CreateTextureFromText(TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (surface == nullptr) {
        SDL_Log("Failed to create surface from text: %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return nullptr;
    }

    textures.push_back(texture); // Store texture for cleanup
    return texture;
}

void TextManager::UnloadFont(TTF_Font* font) {
    for (auto it = fonts.begin(); it != fonts.end(); ++it) {
        if (it->second == font) {
            TTF_CloseFont(font);
            fonts.erase(it);
            return;
        }
    }
}

void TextManager::UnloadTexture(SDL_Texture* texture) {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        if (*it == texture) {
            SDL_DestroyTexture(texture);
            textures.erase(it);
            return;
        }
    }
}

void TextManager::Clean() {
    for (auto& pair : fonts) {
        TTF_CloseFont(pair.second);
    }
    fonts.clear();

    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
    textures.clear();
}