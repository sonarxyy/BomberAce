#include "fade_transition.hpp"

void FadeTransition::fade(SDL_Renderer* renderer, bool fadeIn) {
    SDL_Rect screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (int alpha = fadeIn ? 255 : 0; fadeIn ? alpha >= 0 : alpha <= 255; fadeIn ? alpha -= FADE_SPEED : alpha += FADE_SPEED) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
        SDL_RenderFillRect(renderer, &screenRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
