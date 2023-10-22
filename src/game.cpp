#include "game.hpp"


using namespace sf;

Game::Game() {

    std::ifstream ifs("Config/window.ini");

    std::string gname = "None";
    VideoMode window_bounds(1280, 720);
    unsigned framerate_limit = 120;
    bool verticle_sync_enabled = false;

    if(ifs.is_open()){
        std::getline(ifs, gname);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> verticle_sync_enabled;
    }

    ifs.close();

    this->window = new sf::RenderWindow(window_bounds, gname);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(verticle_sync_enabled);

    this->initStates();
}


Game::~Game() {
    delete this->window;
    while(!this->states.empty()){
        delete this->states.top();
        this->states.pop();
    }
}

void Game::endApplication(){
    std::cout << "Ending Application" << std::endl;
}

void Game::Update() {
    if(!this->states.empty()){
        if(this->states.top()->getQuit()){
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
        this->states.top()->Update(this->dt);
    }
    //end of application
    else{
        this->endApplication();
        this->window->close();
    }
    this->PollEvents();
}

void Game::Render() {
    this->window->clear();

    if(!this->states.empty()){
        this->states.top()->Render();
    }

    this->window->display();
}

RenderWindow * Game::GetWindow() {
    return this->window;
}

void Game::PollEvents() {
    //event polling
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case Event::Closed:
                this->window->close();
                break;
        }
    }
}

void Game::UpdateDT(){
    this->dt = this->dtclock.restart().asSeconds();
}

void Game::Run(){
    while (this->window->isOpen())
    {
        this->UpdateDT();
        this->Update();
        this->Render();
    }
}

void Game::initStates(){
    //this->states.push(new GameStates(this->window));
    this->states.push(new MainMenuState(this->window, &this->states));
}