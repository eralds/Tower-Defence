#ifndef GROUP_3_GAMECLASS
#define GROUP_3_GAMECLASS

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <map>
#include <memory>

#include "button.hpp"
#include "gameStates.hpp"
#include "mainMenuState.hpp"


using namespace sf;

const int SCRWIDTH = 1280;
const int SCRHEIGHT = 720;
const std::string GAMENAME = "Tower Defense";


class Game
{
    
private:
   RenderWindow* window;
    Clock dtclock;
    float dt;
    Event event;
    std::stack<State*> states;
    void initStates();



public:
    //constructors/Destructors
    Game();
    ~Game();

    //functions
        RenderWindow *GetWindow();

    //Render
    void Render();

    //Update
    void Update();
    void UpdateDT();
    void PollEvents();

    //main run
    void Run();

    //main end
    void endApplication();
};
#endif
