#include "main_menu.hpp"

MainMenu::MainMenu(SDL_Renderer* renderer) : renderer(renderer), screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), font(nullptr), selectedOption(Start), selectorSFX(nullptr) {
	textManager = new TextManager(renderer);
	textureManager = new TextureManager(renderer);
	audioManager = new AudioManager();
	GameStateManager::setGameState(InMainMenu);
	CreateDisplay();
}

MainMenu::~MainMenu() {
	delete textureManager;
	delete textManager;
	delete audioManager;
}

void MainMenu::CreateDisplay() {
	// Background
	mainMenuBackground = textureManager->LoadTexture(MAINMENU_BACKGROUND);

	font = textManager->LoadFont(FONT_FILE, 40);
	// Game Title
	gameTitleTexture = textManager->CreateTextureFromText(font, "Shape Dominance", WHITE);
	SDL_QueryTexture(gameTitleTexture, NULL, NULL, &gameTitleRect.w, &gameTitleRect.h);
	gameTitleRect.x = (SCREEN_WIDTH - gameTitleRect.w) / 2;
	gameTitleRect.y = SCREEN_HEIGHT * 2 / 4;

	font = textManager->LoadFont(FONT_FILE, 20);

	// Start
	startTexture = textManager->CreateTextureFromText(font, "Start Game", WHITE);
	SDL_QueryTexture(startTexture, NULL, NULL, &startRect.w, &startRect.h);
	startRect.x = (SCREEN_WIDTH - startRect.w) / 2;
	startRect.y = SCREEN_HEIGHT * 3 / 4;

	// Options
	optionsTexture = textManager->CreateTextureFromText(font, "Options", WHITE);
	SDL_QueryTexture(optionsTexture, NULL, NULL, &optionsRect.w, &optionsRect.h);
	optionsRect.x = (SCREEN_WIDTH - optionsRect.w) / 2;
	optionsRect.y = startRect.y + startRect.h;

	// Quit
	quitTexture = textManager->CreateTextureFromText(font, "Quit", WHITE);
	SDL_QueryTexture(quitTexture, NULL, NULL, &quitRect.w, &quitRect.h);
	quitRect.x = (SCREEN_WIDTH - quitRect.w) / 2;
	quitRect.y = optionsRect.y + optionsRect.h;

	// Selector
	selectorTexture = textureManager->LoadTexture(SELECTOR_TEXTURE_FILE);
	SDL_QueryTexture(selectorTexture, NULL, NULL, &selectorRect.w, &selectorRect.h);
	selectorSFX = audioManager->LoadSound(SELECTOR_SFX_FILE);
	selectedSFX = audioManager->LoadSound(SELECTED_SFX_FILE);

	// Selected
	selectedStartTexture = textManager->CreateTextureFromText(font, "Start Game", YELLOW);
	selectedOptionsTexture = textManager->CreateTextureFromText(font, "Options", YELLOW);
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
			case Options:
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
				break;
			case Quit:
				selectedOption = Options;
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
				selectedOption = Options;
				audioManager->PlaySound(selectorSFX);
				break;
			case Options:
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
			// TODO: Enter other UI when pressing Enter.
			switch (selectedOption) {
			case Start:
				GameStateManager::setGameState(Playing);
				audioManager->PlaySound(selectedSFX);
				break;
			case Options:
				GameStateManager::setGameState(InOptionsMenu);
				audioManager->PlaySound(selectedSFX);
				break;
			case Quit:
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
			if (selectedOption != Start) { // Check if the option changed
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				GameStateManager::setGameState(Playing);
				audioManager->PlaySound(selectedSFX);
			}
		}
		else if (SDL_PointInRect(&mousePoint, &optionsRect)) {
			if (selectedOption != Options) { // Check if the option changed
				selectedOption = Options;
				audioManager->PlaySound(selectorSFX);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				GameStateManager::setGameState(InOptionsMenu);
				audioManager->PlaySound(selectedSFX);
			}
		}
		else if (SDL_PointInRect(&mousePoint, &quitRect)) {
			if (selectedOption != Quit) { // Check if the option changed
				selectedOption = Quit;
				audioManager->PlaySound(selectorSFX);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
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
			case Options:
				selectedOption = Start;
				audioManager->PlaySound(selectorSFX);
				break;
			case Quit:
				selectedOption = Options;
				audioManager->PlaySound(selectorSFX);
				break;
			default:
				break;
			}
		}
		else if (event.wheel.y < 0) { // Scroll down
			switch (selectedOption) {
			case Start:
				selectedOption = Options;
				audioManager->PlaySound(selectorSFX);
				break;
			case Options:
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
	case Options:
		selectedRect = &optionsRect;
		break;
	case Quit:
		selectedRect = &quitRect;
		break;
	default:
		selectedRect = &startRect;
		break;
	}
	selectorRect.x = selectedRect->x - selectorRect.w;
	selectorRect.y = selectedRect->y;
}

void MainMenu::Render() {
	SDL_RenderCopy(renderer, mainMenuBackground, NULL, NULL);
	SDL_RenderCopy(renderer, gameTitleTexture, NULL, &gameTitleRect);
	switch (selectedOption) {
	case Start:
		SDL_RenderCopy(renderer, selectedStartTexture, NULL, &startRect);
		SDL_RenderCopy(renderer, optionsTexture, NULL, &optionsRect);
		SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
		break;
	case Options:
		SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
		SDL_RenderCopy(renderer, selectedOptionsTexture, NULL, &optionsRect);
		SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
		break;
	case Quit:
		SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
		SDL_RenderCopy(renderer, optionsTexture, NULL, &optionsRect);
		SDL_RenderCopy(renderer, selectedQuitTexture, NULL, &quitRect);
		break;
	default:
		break;
	}

	SDL_RenderCopy(renderer, selectorTexture, NULL, &selectorRect);
}