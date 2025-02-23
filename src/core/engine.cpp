#include <engine.hpp>

GameObject* playerObj;
SDL_Texture* backgroundTxt;
AudioManager* audioManager;
Mix_Music* music;

Engine::Engine() : isRunning(false), window(nullptr), renderer(nullptr), music(nullptr) {
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
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Render with supported GPU
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}

	// TODO: Initialize object
	playerObj = new GameObject("assets/purple_body_circle.png", renderer, 0, 0);
	backgroundTxt = TextureManager::LoadTexture("assets/backgroundDesert.png", renderer);
	audioManager = new AudioManager;
	music = audioManager->LoadMusic("assets/music.mp3");
	audioManager->PlayMusic(music);
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
	}
	Clean();
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
	playerObj->Update(deltaTime);
}

void Engine::Render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTxt, 0, 0);
	playerObj->Render();
	SDL_RenderPresent(renderer);
}

void Engine::Clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}