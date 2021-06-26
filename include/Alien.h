#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"


class Alien:public sf::RectangleShape
{
    public:
        Alien();
        int getValue();
        void setValue(int);
        float getXSpeed();
        void setXSpeed(float);
        float getYSpeed();
        void setYSpeed(float);
        float getXPos();
        void setXPos(float);
        float getYPos();
        void setYPos(float);

        Bullet getBullet();

    private:
        int value;
        float xSpeed;
        float ySpeed;
        float xPos;
        float yPos;
        Bullet bullet;
};

#endif // ALIEN_H
