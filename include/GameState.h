#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>

class GameState
{
    public:
        GameState();
        std::string getGameState();
        void setGameState(std::string);

    private:
        std::string state;
};

#endif // GAMESTATE_H
