#include "screen.hpp"

Screen::Screen() {

}

void Screen::Update(RenderWindow* target) {
    for (auto d : buttons) {
        (*d).Update(Vector2f(Mouse::getPosition(*target).x,Mouse::getPosition(*target).y));
    }
}

void Screen::Render(RenderWindow* target) {

    for (auto d : this->sprites) {
        target->draw(d.sprite);
    }
    for (auto d : this->texts) {  
        target->draw(d.text);
    }
    for (auto d : buttons) {
       (*d).Render(target);
    }
}

