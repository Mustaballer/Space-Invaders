#include "GameState.h"

GameState::GameState()
{
    state = "open";
}

std::string GameState::getGameState() {
    return state;
}
void GameState::setGameState(std::string s) {
    state = s;
}

