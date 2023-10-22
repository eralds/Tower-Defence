#ifndef MAP_SELECTOR_STATE_HPP
#define MAP_SELECTOR_STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "mainMenuState.hpp"
#include "state.hpp"
#include "button.hpp"


class MapSelectorState : public State
{
private:
    Texture bgTexture;
    Sprite startBg;
    Font titleFont;
    sf::RectangleShape rect;
    std::map<std::string, Button*> buttons;

    Texture map1Texture;
    Sprite map1Sprite;

    Texture map2Texture;
    Sprite map2Sprite;

    Texture map3Texture;
    Sprite map3Sprite;

public:
    MapSelectorState(RenderWindow* window, std::stack<State*> *states);
    ~MapSelectorState();

    void updateInput(const float& dt);
    void Update(const float& dt);
    void Render(RenderTarget * target = nullptr);
    void endState();
    void initButtons();
    void updateButttons();
    void renderButtons(RenderTarget * target);
};



#endif