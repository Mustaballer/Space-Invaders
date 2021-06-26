#include "Bullet.h"

Bullet::Bullet() {
    setRadius(5);
    setFillColor(sf::Color::Red);
    setOrigin(15, 15);
    setPosition(10, 10);
    /*
    xSpeed = .5;
    ySpeed = .5;
    */
    ySpeed= -10;
}


void Bullet::setYSpeed(float y) {
    ySpeed = y;
}
float Bullet::getYSpeed() {
    return ySpeed;
}

void Bullet::moveBullet() {
    move(0, ySpeed);
}

bool Bullet::getLaunch() {
    return launch;
}
void Bullet::setLaunch(bool x) {
    launch = x;
}









