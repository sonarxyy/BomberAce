#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL.h>
class Engine {
public:
	Engine();
	~Engine();
	bool Initialize(const char* title, int posX, int posY, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
	void HandleEvents();
	void Run();
	void Clean();
	bool getRunningState();

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	void Update();
	void Render();
};

#endif