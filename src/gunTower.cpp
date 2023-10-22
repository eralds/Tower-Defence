#include "gunTower.hpp"

GunTower::GunTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize):Tower()
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
    this->bullet = new Bullet(10, this->sprite.getPosition(), 3);
    
}

GunTower::~GunTower()
{
    delete this->bullet;
}


void GunTower::Update(const sf::Vector2f mousePos, const float& dt){
    wait += dt;
    // bullet animation
    if(this->range.getGlobalBounds().contains(mousePos)){
        this->range.setFillColor(sf::Color(178,178,178,100));
    }
    else{
        this->range.setFillColor(sf::Color(178,178,178,0));
    }

    if(this->isSomeEmemy){
        this->rotate(sf::Vector2i(this->targetEmeny.x,this->targetEmeny.y), this->targetEmeny);
        this->bullet->Update(this->targetEmeny, this->sprite.getPosition());
        this->isHit=true;
    }
    if(isHit && wait >= 2 &&(this->bullet->getBullet().getPosition().x>720 || this->bullet->getBullet().getPosition().x<0 || this->bullet->getBullet().getPosition().y>720 || this->bullet->getBullet().getPosition().y<0)){
        this->bullet->Reload();
        wait = 0;
        isHit = false;
    }
}

void GunTower::Render(sf::RenderTarget* window){
    window->draw(range);
    window->draw(sprite);
    if(this->isSomeEmemy){
        this->bullet->Render(window);
    }
}

void GunTower::rotate(sf::Vector2i mousePos, sf::Vector2f pos){
    double dx = this->sprite.getPosition().x - mousePos.x;
    double dy = this->sprite.getPosition().y - mousePos.y;
    
    if(this->inRange(pos, this->range)){
        this->sprite.setRotation(180+((atan2(dy, dx)) * 180 / M_PI));
    }
}

void GunTower::enemieInRange(std::vector<Enemy*> enemies){
    int j = 0;
    this->isSomeEmemy = false;
    for(auto i: enemies){
        if(this->inRange(i->GetSprite().getPosition(), range)){
            this->targetEmeny = i->GetSprite().getPosition();
            this->isSomeEmemy = true;
            /* if(i->GetSprite().getGlobalBounds().contains(this->bullet->getBullet().getPosition())){
                i->GetHit(this->bullet->damage);
            } */
            return;
        }
        j++;
        
    }
      
}


void GunTower::collisionDetect(std::vector<Enemy*> enemies, float dt){
    for(auto i: enemies){
        if(i->GetSprite().getGlobalBounds().contains(this->bullet->getBullet().getPosition())){
            i->GetHit(this->bullet->damage);
            this->isHit=true;
            return;
        }
    }
}