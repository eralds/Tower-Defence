#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};


using namespace sf;
class Button
{
private:
    short unsigned buttonState;

    RectangleShape shape;
    Font font;
    Text text;

    Color idleColor;
    Color hoverColor;
    Color activeColor;
public:
    Button(float x, float y, float width, float height, std::string text, Font font, Color idleColor, Color hoverColor, Color activeColor);
    ~Button();

    void Render(RenderTarget* target);
    void Update(const Vector2f mousePos);

    //Accessors
    const bool isPressed() const;
};

#endif