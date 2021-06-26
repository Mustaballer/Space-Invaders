#include "Ship.h"

Ship::Ship() {

    setSize(sf::Vector2f(100.f, 30.f));
    setPosition(800.f/2.f, 600.f-30.f);
    //setFillColor(sf::Color::Red);
    setOrigin(50, 15);
}

void Ship::moveShip() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getPosition().x > 50) {
        move(-50, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getPosition().x < 750) {
        move(50, 0);
    }

    //bullet.moveBullet();
}

Bullet Ship::getBullet() {
    return bullet;
}


