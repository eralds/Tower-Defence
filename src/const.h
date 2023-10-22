#ifndef CONST_H
#define CONST_H
#include <iostream>

enum DIRECTION{UP, RIGHT , DOWN, LEFT, IDLE};
static const int MAPDIM = 15;
static const int HEIGHT = 720; 
static const int TILELEN = HEIGHT/MAPDIM;
const std::string mapsDir = "assets/maps/";
const std::string towersDir = "assets/imgs/towers/";
const std::string tilesDir = "assets/imgs/tiles/";
const std::string enemiesDir= "assets/imgs/enemies";
const std::string fontsDir = "assets/fonts/";

#endif