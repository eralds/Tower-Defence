#ifndef TD_TILE_HPP
#define TD_TILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "const.h"

using namespace sf;

class Tile {
    private:
        bool isPath;
        bool isEnd;
        Vector2f position;
        Texture texture;
        Sprite sprite;
        int tileSize;
        int isWater;

        // tower
        bool isOccupied;
    public:
        Tile(std::string path, float x, float y, bool isPath, bool isEnd, bool _isWater);
        void SetSprite(std::string path);
        Sprite GetSprite();
        bool IsPath();
        bool IsEnd();

        bool getIsOccupied() const;
        void setIsOccupied();
        bool IsWater();
        
};

#endif 