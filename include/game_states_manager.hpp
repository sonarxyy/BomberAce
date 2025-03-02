#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

enum GameState {
    InMainMenu,
    InOptionsMenu,
    Playing,
    Paused,
    GameOver,
};

class GameStateManager {
public:
    static GameState getGameState();
    static void setGameState(GameState newState);

private:
    static GameState currentGameState;
};

#endif // GAME_STATE_MANAGER_HPP