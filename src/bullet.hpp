#ifndef BULLET_HPP
#define BULLET_HPP


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath>

class Bullet
{
private:

    sf::Clock time;
    sf::CircleShape bullettShape;

    int speed;
    
    sf::Vector2f originalPos;
public:
    int damage;
    Bullet(float size, sf::Vector2f curPos, int damage);
    ~Bullet();

    void Update(sf::Vector2f targetPos, sf::Vector2f curPos);
    void Render(sf::RenderTarget* targetWindow);
    void Shoot(sf::Vector2f targetPos, sf::Vector2f curPos);

    sf::CircleShape getBullet();

    void Reload();

};




#endif