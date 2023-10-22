#ifndef SATE_HPP
#define SATE_HPP


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

using namespace sf;
class State
{
private:
    // textures
    std::vector<Texture> textures;



protected:
    std::stack<State*> *states;
    RenderWindow* window;
    bool quit;
    Vector2i mousePosScreen;
    Vector2i mousePosWindow;
    Vector2f mousePosView;
public:
    State(RenderWindow* window, std::stack<State*> *states);
    virtual ~State();

    const bool& getQuit() const;
    
    virtual void updateMousePositions();
    virtual void updateInput(const float& dt) = 0;
    virtual void Update(const float& dt) = 0;
    virtual void Render(sf::RenderTarget * target = nullptr) = 0;

    virtual void endState()=0;
};


#endif