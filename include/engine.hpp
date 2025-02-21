#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL.h>
#include <texture_manager.hpp>

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
	TextureManager* textureManager;
	void Update(float deltaTime);
	void Render();
};

#endif