#ifndef TOWERS_HPP
#define TOWERS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath>
#include "enemy.hpp"


class Tower
{
private:
    /* sf::Texture texture;
    sf::Sprite sprite;

    // need to remove later
    sf::CircleShape range; */
    
    
public:
    Tower();
    ~Tower();

    virtual void Update(const sf::Vector2f mousePos, const float& dt)=0;
    virtual void Render(sf::RenderTarget* window)=0;

    virtual void rotate(sf::Vector2i mousePos, sf::Vector2f pos)=0;
    bool inRange(sf::Vector2f mousePos, sf::CircleShape range);

    virtual void enemieInRange(std::vector<Enemy*> enemies)=0;
    virtual void collisionDetect(std::vector<Enemy*> enemies, float dt)=0;
};




#endif