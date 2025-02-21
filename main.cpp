#include <engine.hpp>

Engine* engine = nullptr;
const char* title = "Shape Dominance";
int posX = SDL_WINDOWPOS_UNDEFINED;
int posY = SDL_WINDOWPOS_UNDEFINED;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
bool fullscreen = 0;

int main(int argc, char* argv[]) {
	engine = new Engine();
	engine->Initialize(title, posX, posY, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);
	while (engine->getRunningState()) {
		engine->Run();
	}
	engine->Clean();
	return 0;
}