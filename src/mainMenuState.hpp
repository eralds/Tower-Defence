#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "button.hpp"
#include "state.hpp"
#include "gameStates.hpp"
#include "mapSelectorState.hpp"

class MainMenuState : public State
{
private:
    FloatRect titleRect;    
    Font titleFont;
    Text title;
    Texture bgTexture;
    Sprite startBg;
    Button* start;

    std::map<std::string, Button*> buttons;    
   
public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*> *states);
    ~MainMenuState();

    void updateInput(const float& dt);
    void Update(const float& dt);
    void Render(RenderTarget * target = nullptr);
    void endState();
    void initButtons();
    void updateButttons();
    void renderButtons(RenderTarget * target);
};





#endif