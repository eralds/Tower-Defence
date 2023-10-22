#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "const.h"


class Player
{
    private:
        sf::Font font;
        sf::Text healthText;
        sf::Text coinsText;
        // enemies
        
    public:
        int health = 10;
        int coins = 500;
        Player();
        void Update();
        void Render(sf::RenderWindow* window);
};




#endif