#ifndef FADE_TRANSITION_HPP
#define FADE_TRANSITION_HPP

#include <SDL.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "constants.hpp"

class FadeTransition {
public:
	static void fade(SDL_Renderer* renderer, bool fadeIn);
};

#endif
