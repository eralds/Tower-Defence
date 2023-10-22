#include "mainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*> *states): State(window, states)
{
    //background display + game name
    if(!this->bgTexture.loadFromFile("assets/imgs/mountains.jpg")) {
        std::cout << "Couldn't access path assets/imgs/mountains.jpg " << std::endl;
    }
    this->startBg.setTexture(this->bgTexture);
    if (!this->titleFont.loadFromFile("assets/fonts/Robus.otf"))
    {
        std::cout << "Couldn't access path assets/fonts/Robus.otf" << std::endl;
    }
    this->title.setFont(this->titleFont);
    //maybe change the title
    this->title.setString("Tower Defence");
    this->titleRect = title.getLocalBounds();
    this->title.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top  + titleRect.height/2.0f);
    this->title.setPosition(Vector2f(this->window->getSize().x/2.0f,this->window->getSize().y/3.0f));
    this->title.setFillColor(Color::Black);
    this->title.setCharacterSize(100);

    //Button

    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }
}

void MainMenuState::Update(const float& dt){
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButttons();
}

void MainMenuState::Render(RenderTarget * target){
    if(!target){
        target = this->window;
    }
    this->window->draw(this->startBg);
    this->window->draw(this->title);
    this->renderButtons(target);
}

void MainMenuState::updateInput(const float& dt){
}

void MainMenuState::endState(){
    std::cout << "Ending main menu state" << '\n';
}


void MainMenuState::initButtons(){
    this->buttons["Start"] = new Button(650, 360, 300, 50, "Start", this->titleFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
    this->buttons["Quit"] = new Button(30, 20,100, 50, "Quit", this->titleFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
}

void MainMenuState::updateButttons(){
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->Update(this->mousePosView);
    }

    //Enter gameState
    if(this->buttons["Start"]->isPressed()){
        this->states->push(new MapSelectorState(this->window, this->states));
    }

    //Exit
    if(this->buttons["Quit"]->isPressed()){
        this->quit=true;
    }
}

void MainMenuState::renderButtons(RenderTarget * target){
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->Render(target);
    } 
}