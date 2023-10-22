#include "mapSelectorState.hpp"


MapSelectorState::MapSelectorState(RenderWindow* window, std::stack<State*> *states): State(window, states){
    if(!this->bgTexture.loadFromFile("assets/imgs/mountains.jpg")) {
        std::cout << "Couldn't access path assets/imgs/mountains.jpg " << std::endl;
    }
    this->startBg.setTexture(this->bgTexture);

    if (!this->titleFont.loadFromFile("assets/fonts/Robus.otf"))
    {
        std::cout << "Couldn't access path assets/fonts/Robus.otf" << std::endl;
    }
    this->rect.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
    this->rect.setFillColor(sf::Color(160, 160, 160, 120));
    this->initButtons();

    map1Texture.loadFromFile("assets/imgs/maps/map1.png");
    map2Texture.loadFromFile("assets/imgs/maps/map2.png");
    map3Texture.loadFromFile("assets/imgs/maps/map3.png");

    map1Sprite.setTexture(map1Texture);
    map1Sprite.setPosition(20, 200);
    map1Sprite.setScale(0.3, 0.3);
    map2Sprite.setTexture(map2Texture);
    map2Sprite.setPosition(490, 200);
    map2Sprite.setScale(0.3, 0.3);
    map3Sprite.setTexture(map3Texture);
    map3Sprite.setPosition(960, 200);
    map3Sprite.setScale(0.3, 0.3);
}

MapSelectorState::~MapSelectorState(){
    
}

void MapSelectorState::Update(const float& dt){
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButttons();
}

void MapSelectorState::Render(RenderTarget * target){
    if(!target){
        target = this->window;
    }
    this->window->draw(this->startBg);
    this->window->draw(this->rect);
    this->window->draw(map1Sprite);
    this->window->draw(map2Sprite);
    this->window->draw(map3Sprite);
    this->renderButtons(target);
}

void MapSelectorState::updateInput(const float& dt){
}

void MapSelectorState::endState(){
    std::cout << "Ending Map state" << '\n';
}


void MapSelectorState::initButtons(){
    this->buttons["Map 1"] = new Button(60, 500, 200, 50, "Map One", this->titleFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
    this->buttons["Map 2"] = new Button(520, 500, 200, 50, "Map Two", this->titleFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
    this->buttons["Map 3"] = new Button(1000, 500, 200, 50, "Map Three", this->titleFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
    this->buttons["Back"] = new Button(540, 600, 150, 50, "Back", this->titleFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
}

void MapSelectorState::updateButttons(){
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->Update(this->mousePosView);
    }
    //Back to mainMenu
    if(this->buttons["Back"]->isPressed()){
        this->quit=true;
    }

    if(this->buttons["Map 1"]->isPressed()){
        this->states->push(new GameStates(this->window, this->states, "map1"));
    }

    if(this->buttons["Map 2"]->isPressed()){
        this->states->push(new GameStates(this->window, this->states, "map2"));
    }

    if(this->buttons["Map 3"]->isPressed()){
        this->states->push(new GameStates(this->window, this->states, "map3"));
    }
}


void MapSelectorState::renderButtons(RenderTarget * target){
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->Render(target);
    } 
}