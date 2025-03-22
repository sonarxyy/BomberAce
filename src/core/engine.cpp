#include "engine.hpp"

Engine::Engine(const char* title, int posX, int posY, int screenWidth, int screenHeight, bool fullscreen) : window(nullptr), renderer(nullptr), music(nullptr), player(renderer), isRunning(false)
{
	Initialize(title, posX, posY, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);
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
		isRunning = true;
	}

	// Initialize
	textMananger = new TextManager(renderer);
	textureManager = new TextureManager(renderer);
	audioManager = new AudioManager;
	mainMenu = new MainMenu(renderer);
	optionsMenu = new OptionsMenu(renderer);
	inGame = new InGame(renderer);
	tileManager = new TileManager(renderer);
	return isRunning;
}

bool Engine::GetRunningState() const {
	return isRunning;
}

void Engine::SetRunningState(bool isRunning) {
	Engine::isRunning = isRunning;
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
			keyState = SDL_GetKeyboardState(NULL); // For correct animation based on input for Player
			inGame->HandleInputs(keyState);
			break;
		case Paused:
			break;
		case GameOver:
			break;
		}
	}
}

void Engine::Update(float deltaTime) {
	static GameState previousState = GameStateManager::getGameState();
	GameState currentState = GameStateManager::getGameState();

	if (previousState != currentState) {
		FadeTransition::fade(renderer, false); // Fade out before switching state
	}

	switch (currentState) {
	case InMainMenu:
		mainMenu->UpdateSelectorPosition();
		break;
	case InOptionsMenu:
		optionsMenu->Update();
		break;
	case Playing:
		inGame->Update();
		break;
	case Quitted:
		isRunning = false;
		break;
	}

	if (previousState != currentState) {
		FadeTransition::fade(renderer, false); // Fade in after switching state
		previousState = currentState; // Update stored state
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
	case Playing:
		SDL_RenderClear(renderer);
		tileManager->Render(renderer);
		inGame->Render();
		SDL_RenderPresent(renderer);
		break;
	}
}

void Engine::Clean() {
	delete mainMenu;
	delete optionsMenu;
	delete inGame;
	delete textureManager;
	delete textMananger;
	delete audioManager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}