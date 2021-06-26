#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



class Game
{
    public:
        Game();
        void play();

    private:
        int score;
        int lives;
};

#endif // GAME_H
