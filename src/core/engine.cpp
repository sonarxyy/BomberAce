#include <engine.hpp>

GameObject* playerObj;
SDL_Texture* backgroundTxt;
SDL_Texture* text;
TextureManager* textureManager;
TextManager* textMananger;
AudioManager* audioManager;
Mix_Music* music;
MainMenu* mainMenu;
OptionsMenu* optionsMenu;

Engine::Engine() : isRunning(false), window(nullptr), renderer(nullptr), music(nullptr)
{
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
		SDL_Log("Could not initialize SDL Subsystem");
		isRunning = false;
	}
	else {
		window = SDL_CreateWindow(title, posX, posY, screenWidth, screenHeight, fullscreenFlag);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Render with supported GPU / Sync with refresh rate
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}

	// Initialize
	mainMenu = new MainMenu(renderer);
	optionsMenu = new OptionsMenu(renderer);
	playerObj = new GameObject(PLAYER_FILE, renderer, 0, 0);
	textMananger = new TextManager(renderer);
	text = textMananger->CreateTextureFromText(textMananger->LoadFont(FONT_FILE, 10), "Test", ORANGE);
	textureManager = new TextureManager(renderer);
	audioManager = new AudioManager;
	return isRunning;
}

bool Engine::getRunningState() const {
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
		// SDL_Delay(16); // For better performance
	}
	Clean();
}

void Engine::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		switch (GameStateManager::getGameState()) {
		case InMainMenu:
			mainMenu->HandleInput(event);
			break;
		case InOptionsMenu:
			optionsMenu->HandleInputs(event);
			break;
		case Playing:
			break;
		case Paused:
			break;
		case GameOver:
			break;
		}
	}
}

void Engine::Update(float deltaTime) {
	// TODO: Update everything
	switch (GameStateManager::getGameState()) {
	case InMainMenu:
		mainMenu->UpdateSelectorPosition();
		break;
	case InOptionsMenu:
		optionsMenu->Update();
		break;
	}


}

void Engine::Render() {
	switch (GameStateManager::getGameState()) {
	case InMainMenu:
		SDL_RenderClear(renderer);
		mainMenu->Render();
		SDL_RenderPresent(renderer);
		break;
	case InOptionsMenu:
		SDL_RenderClear(renderer);
		optionsMenu->Render();
		SDL_RenderPresent(renderer);
		break;
	}
}

void Engine::Clean() {
	delete playerObj;
	delete textureManager;
	delete textMananger;
	delete audioManager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}