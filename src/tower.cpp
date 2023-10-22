#include "tower.hpp"

Tower::Tower()
{
    /* this->texture.loadFromFile(_path);
    this->sprite.setTexture(texture);
    this->sprite.scale(resize);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2,this->sprite.getGlobalBounds().height/2);
    this->sprite.setPosition(pos.x+this->sprite.getGlobalBounds().width/2,pos.y+this->sprite.getGlobalBounds().height/2);

    //need to remove later

    this->range.setRadius(100);
    this->range.setOrigin(this->range.getRadius()/2,this->range.getRadius()/2);
    this->range.setPosition(pos);

    // for degbuggging

    std::cout << this->range.getPosition().x << '\t' << this->range.getPosition().y << std::endl << this->sprite.getPosition().x << '\t' << this->sprite.getPosition().y << std::endl; */


 
    
}

Tower::~Tower()
{
}

/* void Tower::Update(const sf::Vector2f mousePos){
    // bullet animation
    if(this->range.getGlobalBounds().contains(mousePos)){
        this->range.setFillColor(sf::Color(178,178,178,200));
    }
    else{
        this->range.setFillColor(sf::Color(178,178,178,0));
    }
}

void Tower::Render(sf::RenderTarget* window){
    window->draw(range);
    window->draw(sprite);
} */

/* void Tower::rotate(sf::Vector2i mousePos){
    double dx = this->sprite.getPosition().x - mousePos.x;
    double dy = this->sprite.getPosition().y - mousePos.y;
    this->sprite.setRotation(180+((atan2(dy, dx)) * 180 / M_PI));
} */

bool Tower::inRange(sf::Vector2f enemyPos, sf::CircleShape range){
    double distx = pow(enemyPos.x-range.getPosition().x,2);
    double disty = pow(enemyPos.y-range.getPosition().y,2);
    double dist = sqrt(distx+disty);


    if(dist <= range.getRadius()){
        return true;
    }
    else{
        return false;
    }
}

