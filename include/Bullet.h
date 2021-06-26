#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Bullet:public sf::CircleShape
{
    public:
        Bullet();
        void setYSpeed(float);
        float getYSpeed();
        void moveBullet();
        bool getLaunch();
        void setLaunch(bool);


    private:
        float ySpeed;
        bool launch;
};

#endif // BULLET_H
