#ifndef TD_SCREEN_HPP
#define TD_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "button.hpp"

using namespace sf;

class Sprite_ {
    public:
        Texture* texture;
        Sprite sprite;
};

class Text_ {
    public:
        Font* font;
        Text text;
};

class Screen {
    private: 

    public:
        std::vector<Sprite_> sprites;
        std::vector<Text_> texts;
        std::vector<Button*> buttons;
        Screen();
        void Update(RenderWindow* target);
        void Render(RenderWindow* target);
        
};

#endif