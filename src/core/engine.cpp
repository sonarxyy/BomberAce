#include <engine.hpp>

Engine::Engine() : isRunning(false), window(nullptr), renderer(nullptr), textureManager(nullptr) {
	// TODO: Init other things
}

Engine::~Engine() {
	Clean();
}

bool Engine::Initialize(const char* title, int posX, int posY, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen) {
	int fullscreenFlag = 0;
	if (fullscreen == true) {
		fullscreenFlag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		// TODO: Handle Error
		SDL_Log("Could not initialize SDL Subsystem");
		isRunning = false;
	}
	else {
		window = SDL_CreateWindow(title, posX, posY, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreenFlag);
		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}

	// TODO: Initialize texture
	textureManager = new TextureManager(renderer);
	

	return isRunning;
}

bool Engine::getRunningState() {
	return isRunning;
}

void Engine::Run() {
	Uint32 lastFrameTime = SDL_GetTicks();
	while (isRunning) {
		Uint32 currentFrameTime = SDL_GetTicks();
		float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
		lastFrameTime = currentFrameTime;

		Update(deltaTime);
		Render();
		Clean();
	}
}

void Engine::HandleEvents() {
	SDL_Event event;
	switch (SDL_PollEvent(&event))
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Engine::Update(float deltaTime) {
	// TODO: Update everything
}

void Engine::Render() {
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Engine::Clean() {
	delete textureManager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}