#include "enemy.hpp"

Enemy::Enemy(int _type, std::string _path,float x, float y, int _health, float _speed, float _size, int _wait, int _reward) {
    this->health = _health;
    this->maxHealth = _health;
    this->speed = _speed;
    this->size = _size;
    this->originalSpeed = _speed;
    this->position = Vector2f(x+(TILELEN/2),y+(TILELEN/2));
    SetSprite(_path); 
    InitHealthBar(x,y);
    wait = _wait;
    reward = _reward;
    type = _type;
}   


void Enemy::SetSprite(std::string _path){
    this->texture.loadFromFile(_path);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2); //origin is at the middle of the tile
    sprite.setScale(Vector2f(size/texture.getSize().x, size/texture.getSize().y));
    this->sprite.setPosition(position);
    // sprite.setOrigin(size/2, size/2); //origin is at the middle of the tile
    // std::cout << _path << " " <<std::to_string(static_cast<int>(size/texture.getSize().y)) << std::endl;

}

void Enemy::Render(RenderWindow *window) {
    window->draw(this->sprite);
    window->draw(healthBar);
    window->draw(healthLeft);
}

void Enemy::Update() {
    position.x += xVelocity;
    position.y += yVelocity;
    distanceTraveled += (abs(xVelocity) + abs(yVelocity));
    this->sprite.setPosition(position);
    healthBar.setPosition(position.x-TILELEN/2, position.y-(TILELEN/2));
    healthLeft.setPosition(position.x-TILELEN/2+3, position.y-(TILELEN/2)+3);
    healthLeft.setSize(Vector2f((TILELEN - 6)*std::max(health,0)/maxHealth, 4));
    // health -= 1;
    // std::cout << " " <<std::to_string(relativePosition.x) << " " <<  std::to_string(relativePosition.y)<< std::endl;

}

void Enemy::SetPath(std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path, int startPos) {
    this->path = _path;
    this->tile = startPos;
    int randTile = std::rand() % ((*path)[tile].size());
    this->nextTile = (*path)[tile].at(randTile).first;
    this->dir = (*path)[tile].at(randTile).second;
    CheckDirection();

}

void Enemy::SetPath(std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path, int startPos,int dist) {
    this->path = _path;
    tile = startPos;
    this->distanceTraveled = dist;
    int randTile = std::rand() % ((*path)[tile].size());
    this->nextTile = (*path)[tile].at(randTile).first;
    this->dir = (*path)[tile].at(randTile).second;
    CheckDirection();
}


void Enemy::UpdatePath() {
    if (distanceTraveled >= TILELEN) {
        tile = nextTile;
        tileNr += 1;
        int randTile = std::rand() % ((*path)[tile].size());
        this->nextTile = (*path)[tile].at(randTile).first;
        this->dir = (*path)[tile].at(randTile).second;
        distanceTraveled = 0;
        CheckDirection();
    }
    else if (distanceTraveled + (abs(xVelocity) + abs(yVelocity)) >= TILELEN) {
        xVelocity = (xVelocity == 0) ? 0 : (TILELEN - distanceTraveled) * (xVelocity/abs(xVelocity));
        yVelocity = (yVelocity == 0) ? 0 : (TILELEN - distanceTraveled) * (yVelocity/abs(yVelocity)); 
    }
   
}

bool Enemy::CheckEndOfPath() {
    if (tile == (*path)[tile].front().first) {
        std::cout << "reached end tile" << std::endl;
        return true;
    }   
    return false;
}

void Enemy::InitHealthBar(float x, float y) {
    healthBar.setPosition(position.x-TILELEN/2, position.y-(TILELEN/2));
    healthLeft.setPosition(position.x-TILELEN/2+3, position.y-(TILELEN/2)+3);
    healthBar.setSize(Vector2f(TILELEN, 10));
    healthLeft.setSize(Vector2f(TILELEN - 6, 4));
    healthBar.setFillColor(sf::Color(0x2b2b2bff));
    healthLeft.setFillColor(Color::Red);
}

void Enemy::CheckDirection() {
    switch (dir) {
        case UP:
            yVelocity = 0-speed;
            xVelocity = 0;
            break;
        case DOWN:
            yVelocity = speed;
            xVelocity = 0;
            break;
        case LEFT:
            xVelocity = 0-speed;
            yVelocity = 0;
            break;
        case RIGHT:
            xVelocity = speed;
            yVelocity = 0;
            break;
        case IDLE:
            xVelocity = 0;
            yVelocity = 0;
            break;
        }
    this->sprite.setRotation(this->dir * 90.0);
}

int Enemy::GetWait(){
    return wait;
}
Enemy::~Enemy(){
    
}

sf::Sprite Enemy::GetSprite(){
    return this->sprite;
}

bool Enemy::CheckIfDead(){
    return (health <= 0);
}

int Enemy::GetTileNr() {
   return tileNr;
}

void Enemy::GetHit(int damage){
   this->health =this->health- damage;
}

int Enemy::GetReward() {
    return reward;
}

void Enemy::setSpeed(float newSpeed){
    this->speed = newSpeed;
}

float Enemy::getOriginalSpeed(){
    return this->originalSpeed;
}

const int Enemy::GetType() {
    return type;
}

sf::Vector2f Enemy::GetPosition(){
    return sf::Vector2f(position.x - (TILELEN/2), position.y - (TILELEN/2)) ;
}
int Enemy::GetCurTile() {
    return tile;
}
int Enemy::GetDist(){
    return distanceTraveled;
}

void Enemy::SetFrozenEffect(){
    sprite.setColor(sf::Color(0,191,255));
}

void Enemy::RemoveFrozenEffect(){
    sprite.setColor(sf::Color(255,255,255));
}