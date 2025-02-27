#include "main_menu.hpp"

MainMenu::MainMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer), screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), font(nullptr), selectedOption(Start), selectorSFX(nullptr) {
	textManager = new TextManager(renderer);
	textureManager = new TextureManager(renderer);
	audioManager = new AudioManager();
	CreateDisplay();
}

MainMenu::~MainMenu() {
	delete textureManager;
	delete textManager;
}

void MainMenu::CreateDisplay() {
	// Background
	mainMenuBackground = textureManager->LoadTexture(MAINMENU_BACKGROUND);

	font = textManager->LoadFont(FONT_FILE, 40);
	// Game Title
	gameTitleTexture = textManager->CreateTextureFromText(font, "Shape Dominance", WHITE);

	gameTitleRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	gameTitleRect.y = SCREEN_HEIGHT * 2 / 4;
	gameTitleRect.w = textManager->getWidth();
	gameTitleRect.h = textManager->getHeight();

	font = textManager->LoadFont(FONT_FILE, 20);

	// Start
	startTexture = textManager->CreateTextureFromText(font, "Start Game", WHITE);

	startRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	startRect.y = SCREEN_HEIGHT * 3 / 4;
	startRect.w = textManager->getWidth();
	startRect.h = textManager->getHeight();


	// Options
	optionsTexture = textManager->CreateTextureFromText(font, "Options", WHITE);

	optionsRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	optionsRect.y = startRect.y + startRect.h;
	optionsRect.w = textManager->getWidth();
	optionsRect.h = textManager->getHeight();

	// Quit
	quitTexture = textManager->CreateTextureFromText(font, "Quit", WHITE);

	quitRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	quitRect.y = optionsRect.y + optionsRect.h;
	quitRect.w = textManager->getWidth();
	quitRect.h = textManager->getHeight();

	// Selector
	selectorTexture = textureManager->LoadTexture(SELECTOR_TEXTURE_FILE);
	SDL_QueryTexture(selectorTexture, NULL, NULL, &selectorRect.w, &selectorRect.h); //get width and height
	selectorSFX = audioManager->LoadSound(SELECTOR_SFX_FILE);
}

void MainMenu::HandleInput(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			switch (selectedOption) {
			case MenuOption::Start:
				selectedOption = MenuOption::Quit;
				audioManager->PlaySound(selectorSFX);
				break;
			case MenuOption::Options:
				selectedOption = MenuOption::Start;
				audioManager->PlaySound(selectorSFX);
				break;
			case MenuOption::Quit:
				selectedOption = MenuOption::Options;
				audioManager->PlaySound(selectorSFX);
				break;
			default:
				break;
			}
			break;
		case SDLK_DOWN:
		case SDLK_s:
			switch (selectedOption) {
			case MenuOption::Start:
				selectedOption = MenuOption::Options;
				audioManager->PlaySound(selectorSFX);
				break;
			case MenuOption::Options:
				selectedOption = MenuOption::Quit;
				audioManager->PlaySound(selectorSFX);
				break;
			case MenuOption::Quit:
				selectedOption = MenuOption::Start;
				audioManager->PlaySound(selectorSFX);
				break;
			default:
				break;
			}
			break;
		case SDLK_RETURN:
			// TODO: Enter other UI when pressing Enter.
			break;
		default:
			break;
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
	SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
	SDL_RenderCopy(renderer, optionsTexture, NULL, &optionsRect);
	SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
	SDL_RenderCopy(renderer, selectorTexture, NULL, &selectorRect);
}