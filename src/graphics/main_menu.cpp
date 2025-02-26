#include "main_menu.hpp"

MainMenu::MainMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer), screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), font(nullptr) {
	textManager = new TextManager(renderer);
	textureManager = new TextureManager(renderer);
	CreateDisplay();
}

MainMenu::~MainMenu() {

}

void MainMenu::CreateDisplay() {
	// Background
	mainMenuBackground = textureManager->LoadTexture(MAINMENU_BACKGROUND);

	font = textManager->LoadFont(FONT_FILE, 40);
	// Game Title
	gameTitleTexture = textManager->CreateTextureFromText(font, "Shape Dominance", BLACK);

	gameTitleRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	gameTitleRect.y = SCREEN_HEIGHT * 2 / 4;
	gameTitleRect.w = textManager->getWidth();
	gameTitleRect.h = textManager->getHeight();

	font = textManager->LoadFont(FONT_FILE, 20);

	// Start
	startTexture = textManager->CreateTextureFromText(font, "Start Game", BLACK);

	startRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	startRect.y = SCREEN_HEIGHT * 3 / 4;
	startRect.w = textManager->getWidth();
	startRect.h = textManager->getHeight();


	// Options
	optionsTexture = textManager->CreateTextureFromText(font, "Options", BLACK);

	optionsRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	optionsRect.y = startRect.y + startRect.h;
	optionsRect.w = textManager->getWidth();
	optionsRect.h = textManager->getHeight();

	// Quit
	quitTexture = textManager->CreateTextureFromText(font, "Quit", BLACK);

	quitRect.x = (SCREEN_WIDTH - textManager->getWidth()) / 2;
	quitRect.y = optionsRect.y + optionsRect.h;
	quitRect.w = textManager->getWidth();
	quitRect.h = textManager->getHeight();

}

void MainMenu::Render() {
	SDL_RenderCopy(renderer, mainMenuBackground, NULL, NULL);
	SDL_RenderCopy(renderer, gameTitleTexture, NULL, &gameTitleRect);
	SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
	SDL_RenderCopy(renderer, optionsTexture, NULL, &optionsRect);
	SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
}