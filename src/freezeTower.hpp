#ifndef FREEZE_TOWER_HPP
#define FREEZE_TOWER_HPP


#include "tower.hpp"
#include "bullet.hpp"
#include "enemy.hpp"


class FreezeTower: public Tower
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

   
    sf::CircleShape range;

    sf::Vector2f targetEmeny;
    bool isSomeEmemy;


    float wait = 0;

    bool isHit = false;
    // slows down enemy 
    float speedMulti = 0.5;   

public:
    FreezeTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize);
    ~FreezeTower();


    void Update(const sf::Vector2f mousePos, const float& dt);
    void Render(sf::RenderTarget* window);
    void rotate(sf::Vector2i mousePos, sf::Vector2f pos);
    void enemieInRange(std::vector<Enemy*> enemies);

    void collisionDetect(std::vector<Enemy*> enemies, float dt);
};




#endif