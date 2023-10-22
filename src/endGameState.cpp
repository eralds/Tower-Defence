#include "endGameState.hpp"

EndGameState::EndGameState(sf::RenderWindow* window, std::stack<State*> *states, std::string msg): State(window, states)
{
    //background display + game name
    if(!this->bgTexture.loadFromFile("assets/imgs/mountains.jpg")) {
        std::cout << "Couldn't access path assets/imgs/mountains.jpg " << std::endl;
    }
    this->startBg.setTexture(this->bgTexture);
    if (!this->messageFont.loadFromFile("assets/fonts/Robus.otf"))
    {
        std::cout << "Couldn't access path assets/fonts/Robus.otf" << std::endl;
    }
    this->message.setFont(this->messageFont);
    //maybe change the message
    this->message.setString(msg);
    this->message.setPosition(Vector2f(this->window->getSize().x/3.0f - (msg == "Victory" ? 40.0 : 0.0),this->window->getSize().y/5.0f));
    this->message.setFillColor(Color::Black);
    this->message.setCharacterSize(200);

    //Button

    this->initButtons();
}

EndGameState::~EndGameState()
{
    delete mainMenuBtn;
}

void EndGameState::Update(const float& dt){
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButttons();
}

void EndGameState::Render(RenderTarget * target){
    if(!target){
        target = this->window;
    }
    this->window->draw(this->startBg);
    this->window->draw(this->message);
    this->renderButtons(target);
}

void EndGameState::updateInput(const float& dt){
}

void EndGameState::endState(){
    std::cout << "Ending end game state" << '\n';
}


void EndGameState::initButtons(){
    this->mainMenuBtn = new Button(500, 600, 300, 50, "Back to Menu", this->messageFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
}

void EndGameState::updateButttons(){
    
    mainMenuBtn->Update(this->mousePosView);

    //Enter gameState
    if(this->mainMenuBtn->isPressed()){
        this->states->push(new MapSelectorState(this->window, this->states));
    }

}

void EndGameState::renderButtons(RenderTarget * target){
    mainMenuBtn->Render(target);
}