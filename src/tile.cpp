#include "tile.hpp"

Tile::Tile(std::string path, float x, float y, bool _isPath, bool _isEnd, bool _isWater) {
    this->position = Vector2f(x,y);
    this->sprite.setPosition(position);
    this->isPath = _isPath;
    this->isEnd = _isEnd;
    this->isWater = _isWater;
    SetSprite(path);
}   

void Tile::SetSprite(std::string path){
    if(!this->texture.loadFromFile(path)) {
        std::cout << "Couldn't access path" << path << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,TILELEN, TILELEN));
}

Sprite Tile::GetSprite() {
    return this->sprite;
}

bool Tile::IsPath() {
    return this->isPath;
}

bool Tile::IsEnd() {
    return this->isEnd;
}

bool Tile::getIsOccupied()const{
    return this->isOccupied;
}

void Tile::setIsOccupied(){
    this->isOccupied = true;
}

bool Tile::IsWater(){
    return this->isWater;
}