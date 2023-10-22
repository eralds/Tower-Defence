#ifndef TD_MAP_HPP
#define TD_MAP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
// #include <sstream>
#include <fstream>
#include <list>
#include <map>
#include "tile.hpp"
#include "const.h"


using namespace sf;

// enum DIR{UP, DOWN, LEFT, RIGHT};

class Map {
    private:
        Tile *tiles[MAPDIM][MAPDIM]; // [vertical][horizontal]
        std::pair<int, int> startPos;
        std::list<std::list<DIRECTION>> path; //v1
        std::map<int ,std::vector<std::pair<int,DIRECTION>>> pathMap; //v2


    public:
    
        Map(std::string _path);
        void Render(RenderWindow *window);
        void Update();
        void CreatePath();
        std::map<int ,std::vector<std::pair<int,DIRECTION>>>* GetPath();
        std::pair<int, int> GetStartPos();
        Tile* GetTile(std::pair<int, int>);
        std::vector<std::pair<std::pair<int, int>,DIRECTION>> Neighbours(std::pair<int, int>);
};

#endif 