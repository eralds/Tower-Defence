#ifndef BAZOOKA_TOWER_HPP
#define BAZOOKA_TOWER_HPP


#include "tower.hpp"
#include "bullet.hpp"
#include "enemy.hpp"


class BazookaTower: public Tower
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

   
    sf::CircleShape range;

    sf::Vector2f targetEmeny;
    bool isSomeEmemy;

    Bullet *bullet;
    float bulletRange;

    float wait = 0;

    bool isHit = false;   

public:
    BazookaTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize);
    ~BazookaTower();


    void Update(const sf::Vector2f mousePos, const float& dt);
    void Render(sf::RenderTarget* window);
    void rotate(sf::Vector2i mousePos, sf::Vector2f pos);
    void enemieInRange(std::vector<Enemy*> enemies);

    void collisionDetect(std::vector<Enemy*> enemies, float dt);
};



#endif