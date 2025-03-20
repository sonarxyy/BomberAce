#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SDL.h>

// Window title
constexpr const char* title = "Shape Dominance";

// Screen resolution
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = SCREEN_WIDTH;

// Color
const SDL_Color CYAN = { 0, 255, 255 };
const SDL_Color BLUE = { 0, 0, 255 };
const SDL_Color ORANGE = { 255, 165, 0 };
const SDL_Color YELLOW = { 255, 255, 0 };
const SDL_Color LIME = { 0, 255, 0 };
const SDL_Color PURPLE = { 128, 0, 128 };
const SDL_Color RED = { 255, 0, 0 };
const SDL_Color WHITE = { 255, 255, 255 };
const SDL_Color BLACK = { 0, 0, 0 };
const SDL_Color GREEN = { 0, 128, 0 };

// Path (using constexpr to avoid linker error)
// Main Menu Path
constexpr const char* OPEN_SANS_FONT_FILE = "assets/font/open_sans_font.ttf";
constexpr const char* XIROD_FONT_FILE = "assets/font/xirod_font.ttf";
constexpr const char* MUSIC_FILE = "assets/audio/music.mp3";
constexpr const char* SELECTOR_SFX_FILE = "assets/audio/selector_sfx.ogg";
constexpr const char* SELECTED_SFX_FILE = "assets/audio/selected_sfx.ogg";
constexpr const char* SELECTOR_TEXTURE_FILE = "assets/image/selector.png";
constexpr const char* MAINMENU_BACKGROUND = "assets/image/mainmenubackground.png";
constexpr const char* MAINMENU_BOX = "assets/image/button_rectangle_depth_border.png";

// Options Menu Path
constexpr const char* OPTIONSMENU_BACKGROUND = "assets/image/optionsmenubackground.png";

// In Game Path
constexpr const char* PLAYER_FILE = "assets/image/purple_body_circle.png";
constexpr const char* BACKGROUND_DESERT_FILE = "assets/image/backgroundColorDesert.png";
constexpr const char* BACKGROUND_FALL_FILE = "assets/image/backgroundColorFall.png";
constexpr const char* BACKGROUND_FOREST_FILE = "assets/image/backgroundColorForest.png";
constexpr const char* BACKGROUND_GRASS_FILE = "assets/image/backgroundColorGrass.png";

// Tile generation
const int MAP_ROWS = 20;
const int MAP_COLS = 20;
const int TILE_SIZE = SCREEN_WIDTH / 20;

// For animation
const int FRAME = 30;

#endif