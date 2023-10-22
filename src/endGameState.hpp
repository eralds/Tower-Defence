#ifndef END_GAME_STATE_HPP
#define END_GAME_STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "button.hpp"
#include "state.hpp"
#include "gameStates.hpp"
#include "mapSelectorState.hpp"

class EndGameState : public State
{
private:
    FloatRect messageRect;    
    Font messageFont;
    Text message;
    Texture bgTexture;
    Sprite startBg;
    Button* start;

    Button* mainMenuBtn;    
   
public:
    EndGameState(sf::RenderWindow* window, std::stack<State*> *states, std::string);
    ~EndGameState();

    void updateInput(const float& dt);
    void Update(const float& dt);
    void Render(RenderTarget * target = nullptr);
    void endState();
    void initButtons();
    void updateButttons();
    void renderButtons(RenderTarget * target);
};





#endif