#include "boat.hpp"

BoatTower::BoatTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize, Player *player):Tower()
{
    this->texture.loadFromFile(_path);
    this->sprite.setTexture(texture);
    this->sprite.scale(resize);
    this->sprite.setOrigin(this->texture.getSize().x/2,this->texture.getSize().y/2 );
    this->sprite.setPosition(pos.x+24,pos.y+24);


    this->range.setRadius(150);
    this->range.setOrigin(this->range.getRadius(),this->range.getRadius());
    this->range.setPosition(pos.x+24,pos.y+24);

    this->isSomeEmemy = false;
    this->player=player;
    
}

BoatTower::~BoatTower()
{
}


void BoatTower::Update(const sf::Vector2f mousePos, const float& dt){
    wait += dt;

    if(wait >= 10){
       this->player->coins+=50;
       this->wait=0;
    }
}

void BoatTower::Render(sf::RenderTarget* window){
    window->draw(sprite);
}

void BoatTower::rotate(sf::Vector2i mousePos, sf::Vector2f pos){
/*     double dx = this->sprite.getPosition().x - mousePos.x;
    double dy = this->sprite.getPosition().y - mousePos.y;
    
    if(this->inRange(pos, this->range)){
        this->sprite.setRotation(180+((atan2(dy, dx)) * 180 / M_PI));
    } */
}

void BoatTower::enemieInRange(std::vector<Enemy*> enemies){
/*     int j = 0;
    this->isSomeEmemy = false;
    for(auto i: enemies){
        if(this->inRange(i->GetSprite().getPosition(), range)){
            this->targetEmeny = i->GetSprite().getPosition();
            this->isSomeEmemy = true;
            i->setSpeed(i->getOriginalSpeed()*this->speedMulti);
        }
        else{
            i->setSpeed(i->getOriginalSpeed());
        }
        j++;    
    } */    
}


void BoatTower::collisionDetect(std::vector<Enemy*> enemies, float dt){
}