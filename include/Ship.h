#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Bullet.h"

class Ship:public sf::RectangleShape
{
    public:
        Ship();
        void moveShip();
        Bullet getBullet();


    private:
        Bullet bullet;
};

#endif // SHIP_H
