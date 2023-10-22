#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <utility>

#include "mainMenuState.hpp"
#include "state.hpp"
#include "map.hpp"
#include "const.h"
#include "enemy.hpp"
#include "tower.hpp"
#include "wave.hpp"
#include "gunTower.hpp"
#include "freezeTower.hpp"
#include "bazookaTower.hpp"
#include "boat.hpp"
#include "player.hpp"
#include "endGameState.hpp"

#include "button.hpp"
#include <cmath>


class GameStates : public State
{
private:
    Map *map;
    std::map<int ,std::vector<std::pair<int,DIRECTION>>> * path;
    std::pair<int, int> startPos;

    Player *player;

    // waves
    std::vector<Wave*> waves;

    // towers
    std::vector<Tower*> towers;



    // For gui drag and drop
    sf::RectangleShape towerSpace;

    // for tower 1 gun tower
    sf::Texture t1;
    sf::Sprite tower1;
    bool isPressed1 = false;
    int t1Cost;

    // For tower 2 freeze tower
    sf::Texture t2;
    sf::Sprite tower2;
    bool isPressed2 = false;
    int t2Cost;

    // For Bazooka tower
    sf::Texture t3;
    sf::Sprite tower3;
    bool isPressed3 = false;
    int t3Cost;

    // For Boat 
    sf::Texture t4;
    sf::Sprite tower4;
    bool isPressed4 = false;
    int t4Cost;
    

    // Dragging
    
    sf::Texture d;
    sf::Sprite drag;
   
   // Dropping


    // buttons
    std::map<std::string, Button*> buttons; 
    Font titleFont;
    Font font;


public:
    GameStates(RenderWindow* window, std::stack<State*> *states, std::string mapName);
    ~GameStates();

    void updateInput(const float& dt);
    void Update(const float& dt);
    void Render(RenderTarget * target = nullptr);
    void endState();
    

    // dragging
    void updateDrag();
    void renderDrag();

    // buttons
    void initButtons();
    void updateButttons();
    void renderButtons(RenderTarget * target);

    // direction of enemy 
    

};



#endif