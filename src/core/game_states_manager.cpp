#include <game_states_manager.hpp>

GameState GameStateManager::currentGameState = InMainMenu;

GameState GameStateManager::getGameState() {
    return GameStateManager::currentGameState;
}

void GameStateManager::setGameState(GameState newState) {
    GameStateManager::currentGameState = newState;
}