#include "main_menu.hpp"

MainMenu::MainMenu(SDL_Renderer* renderer) : renderer(renderer), font(nullptr), selectedOption(Start), selectorSFX(nullptr) {
	textManager = new TextManager(renderer);
	textureManager = new TextureManager(renderer);
	audioManager = new AudioManager();
	GameStateManager::setGameState(InMainMenu);
	// Initialize animation variables
	CreateDisplay();
	animationTimer = 0;
	animationSpeed = 3; // Adjust for animation speed
}

MainMenu::~MainMenu() {
	delete textureManager;
	delete textManager;
	delete audioManager;
}

void MainMenu::CreateDisplay() {
	// Background
	mainMenuBackground = textureManager->LoadTexture(MAINMENU_BACKGROUND);

	// Game Title
	font = textManager->LoadFont(XIROD_FONT_FILE, 40);
	gameTitleTexture = textManager->CreateTextureFromText(font, "Bomber Ace", WHITE);
	SDL_QueryTexture(gameTitleTexture, NULL, NULL, &gameTitleRect.w, &gameTitleRect.h);
	gameTitleRect.x = 20; // Left aligned (adjust as needed)
	gameTitleRect.y = SCREEN_HEIGHT / 6;

	// Start
	font = textManager->LoadFont(XIROD_FONT_FILE, 20); // Resize font
	startTexture = textManager->CreateTextureFromText(font, "Start Game", WHITE);
	SDL_QueryTexture(startTexture, NULL, NULL, &startRect.w, &startRect.h);
	startRect.x = 20; // Left aligned
	startRect.y = SCREEN_HEIGHT / 2; // Start position

	// Quit
	quitTexture = textManager->CreateTextureFromText(font, "Quit", WHITE);
	SDL_QueryTexture(quitTexture, NULL, NULL, &quitRect.w, &quitRect.h);
	quitRect.x = 20; // Left aligned
	quitRect.y = startRect.y + startRect.h + 5; // Spacing

	// Selector
	selectorTexture = textureManager->LoadTexture(SELECTOR_TEXTURE_FILE);
	SDL_QueryTexture(selectorTexture, NULL, NULL, &selectorRect.w, &selectorRect.h);
	selectorSFX = audioManager->LoadSound(SELECTOR_SFX_FILE);
	selectedSFX = audioManager->LoadSound(SELECTED_SFX_FILE);

	// Selected
	selectedStartTexture = textManager->CreateTextureFromText(font, "Start Game", YELLOW);
	selectedQuitTexture = textManager->CreateTextureFromText(font, "Quit", YELLOW);
}



void MainMenu::HandleInput(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) { // Check for keyboard event
		switch (event.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			switch (selectedOption) {
			case Start:
				selectedOption = Quit;
				audioManager->PlaySound(selectorSFX);
				break;
			case Quit:
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
				break;
			default:
				break;
			}
			break;
		case SDLK_DOWN:
		case SDLK_s:
			switch (selectedOption) {
			case Start:
				selectedOption = Quit;
				audioManager->PlaySound(selectorSFX);
				break;
			case Quit:
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
				break;
			default:
				break;
			}
			break;
		case SDLK_RETURN:
			switch (selectedOption) {
			case Start:
				GameStateManager::setGameState(Playing);
				audioManager->PlaySound(selectedSFX);
				break;
			case Quit:
				GameStateManager::setGameState(Quitted);
				SDL_Event quitEvent;
				quitEvent.type = SDL_QUIT;
				SDL_PushEvent(&quitEvent);
				break;
			}
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) { // Check for mouse motion event
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		SDL_Point mousePoint = { mouseX, mouseY }; // Create a point for the mouse

		if (SDL_PointInRect(&mousePoint, &startRect)) {
			if (selectedOption != Start) {
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
				animationTimer = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				GameStateManager::setGameState(Playing);
				audioManager->PlaySound(selectedSFX);
			}
		}
		else if (SDL_PointInRect(&mousePoint, &quitRect)) {
			if (selectedOption != Quit) {
				selectedOption = Quit;
				audioManager->PlaySound(selectorSFX);
				animationTimer = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				GameStateManager::setGameState(Quitted);
				SDL_Event quitEvent;
				quitEvent.type = SDL_QUIT;
				SDL_PushEvent(&quitEvent);
			}
		}
	} else if (event.type == SDL_MOUSEWHEEL) { // Handle mouse wheel events
		if (event.wheel.y > 0) { // Scroll up
			switch (selectedOption) {
			case Start:
				selectedOption = Quit;
				audioManager->PlaySound(selectorSFX);
				break;
			case Quit:
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
				break;
			default:
				break;
			}
		}
		else if (event.wheel.y < 0) { // Scroll down
			switch (selectedOption) {
			case Start:
				selectedOption = Quit;
				audioManager->PlaySound(selectorSFX);
				break;
			case Quit:
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
				break;
			default:
				break;
			}
		}
	}
}

void MainMenu::UpdateSelectorPosition() {
	SDL_Rect* selectedRect;
	switch (selectedOption) {
	case Start:
		selectedRect = &startRect;
		break;
	case Quit:
		selectedRect = &quitRect;
		break;
	default:
		selectedRect = &startRect;
		break;
	}
	selectorRect.x = selectedRect->x - selectorRect.w;
	selectorRect.y = selectedRect->y + selectedRect->h - selectorRect.h;
}

void MainMenu::Render() {
	SDL_RenderCopy(renderer, mainMenuBackground, NULL, NULL);
	SDL_RenderCopy(renderer, gameTitleTexture, NULL, &gameTitleRect);

	int offset = sin(animationTimer / 15.0) * 2;
	animationTimer += animationSpeed;

	SDL_Rect animatedRect;

	switch (selectedOption) {
	case Start:
		animatedRect = startRect;
		animatedRect.y += offset;
		SDL_RenderCopy(renderer, selectedStartTexture, NULL, &animatedRect);
		SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
		break;
	case Quit:
		SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
		animatedRect = quitRect;
		animatedRect.y += offset;
		SDL_RenderCopy(renderer, selectedQuitTexture, NULL, &animatedRect);

		break;
	default:
		break;
	}

	SDL_RenderCopy(renderer, selectorTexture, NULL, &selectorRect);
}