#include "Alien.h"

Alien::Alien()
{
    setSize(sf::Vector2f(75, 15));
    setOrigin(75/2, 15/2);
    setFillColor(sf::Color::Cyan);
    setPosition(800/2,600/2);
    ySpeed = .5; // adjust rn for testing
    xSpeed = 5;
}

int Alien::getValue() {
    return value;
}
void Alien::setValue(int x) {
    value = x;
}

Bullet Alien::getBullet(){
    return bullet;
}

float Alien::getXSpeed() {
    return xSpeed;
}
void Alien::setXSpeed(float x) {
    xSpeed = x;
}

float Alien::getYSpeed() {
    return ySpeed;
}
void Alien::setYSpeed(float x) {
    ySpeed = x;
}

float Alien::getXPos() {
    return xPos;
}
void Alien::setXPos(float x) {
    xPos = x;
}
float Alien::getYPos() {
    return yPos;
}
void Alien::setYPos(float y) {
    yPos = y;
}


