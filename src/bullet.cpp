#include "bullet.hpp"

Bullet::Bullet(float size, sf::Vector2f curPos, int damage)
{
    this->bullettShape.setRadius(size);
    this->bullettShape.setFillColor(sf::Color::White);
    this->bullettShape.setPosition(curPos);

    this->speed = 2;
    this->originalPos = curPos;
    this->damage=damage;
}

Bullet::~Bullet()
{

}


void Bullet::Shoot(sf::Vector2f targetPos, sf::Vector2f curPos){
    float dt = 1/time.getElapsedTime().asSeconds();
    sf::Vector2f source = targetPos-curPos;
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    source.x = source.x / length;
    source.y =  source.y / length;
    bullettShape.move(source * 10.f);




    time.restart();
}

void Bullet::Update(sf::Vector2f targetPos, sf::Vector2f curPos){
    this->Shoot(targetPos, curPos);
}

void Bullet::Render(sf::RenderTarget* targetWindow){
    targetWindow->draw(this->bullettShape);
}

sf::CircleShape Bullet::getBullet(){
    return this->bullettShape;
}

void Bullet::Reload(){
    this->bullettShape.setPosition(originalPos);
}