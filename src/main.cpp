#include "engine.hpp"

Engine* engine = nullptr;
int posX = SDL_WINDOWPOS_UNDEFINED;
int posY = SDL_WINDOWPOS_UNDEFINED;
bool fullscreen = 0;

int main(int argc, char* argv[]) {
	engine = new Engine(title, posX, posY, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);
	while (engine->getRunningState()) {
		engine->Run();
	}
	engine->Clean();
	return 0;
}