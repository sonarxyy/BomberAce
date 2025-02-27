#include <engine.hpp>

GameObject* playerObj;
SDL_Texture* backgroundTxt;
SDL_Texture* text;
TextureManager* textureManager;
TextManager* textMananger;
AudioManager* audioManager;
Mix_Music* music;
MainMenu* mainMenu;

Engine::Engine() : isRunning(false), window(nullptr), renderer(nullptr), music(nullptr)
{
	gameState = InMainMenu;
	// TODO: Init other things
}

Engine::~Engine() {
	Clean();
}

bool Engine::Initialize(const char* title, int posX, int posY, int screenWidth, int screenHeight, bool fullscreen) {
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
		window = SDL_CreateWindow(title, posX, posY, screenWidth, screenHeight, fullscreenFlag);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Render with supported GPU
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}

	// Initialize
	mainMenu = new MainMenu(renderer, screenWidth, screenHeight);
	mainMenu->Render();
	playerObj = new GameObject(PLAYER_FILE, renderer, 0, 0);
	textMananger = new TextManager(renderer);
	text = textMananger->CreateTextureFromText(textMananger->LoadFont(FONT_FILE, 10), "Test", ORANGE);
	textureManager = new TextureManager(renderer);
	audioManager = new AudioManager;
	// music = audioManager->LoadMusic(MUSIC_FILE);
	// audioManager->PlayMusic(music);
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

		HandleEvents();
		Update(deltaTime);
		Render();
	}
	Clean();
}

void Engine::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (gameState) {
		case InMainMenu:
			mainMenu->HandleInput(event);
			break;
		case GameOver:
			break;
		}
	}
}

void Engine::Update(float deltaTime) {
	// TODO: Update everything
	// playerObj->Update(deltaTime);
	mainMenu->UpdateSelectorPosition();
}

void Engine::Render() {
	/*
	SDL_RenderCopy(renderer, backgroundTxt, 0, 0);
	SDL_RenderCopy(renderer, text, 0, 0);
	playerObj->Render();*/
	SDL_RenderClear(renderer);
	mainMenu->Render();
	SDL_RenderPresent(renderer);
}

void Engine::Clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}