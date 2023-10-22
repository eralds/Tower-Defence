#include "gameStates.hpp"


GameStates::GameStates(RenderWindow* window, std::stack<State*> *states, std::string mapName): State(window, states){
    this->map = new Map(mapsDir + mapName + ".csv");
    this->path = this->map->GetPath();
    this->startPos = this->map->GetStartPos();

    player = new Player();

    std::srand(std::time(nullptr));

    this->waves.push_back(new Wave("Wave 1" , 5,0,0,0,0, startPos, player));
    this->waves.push_back(new Wave("Wave 2" , 10,5,0,0,0, startPos, player));
    this->waves.push_back(new Wave("Wave 3" , 5,0,5,0,0, startPos, player));
    this->waves.push_back(new Wave("Wave 4" , 0,5,5,5,0, startPos, player));
    this->waves.push_back(new Wave("Wave 5" , 0,0,0,0,2, startPos, player));

    for (auto i: waves) {
        i->SetPath(path);
    }

    // for tower 1 gun_tower
    this->towerSpace.setSize(sf::Vector2f(560,720));
    this->towerSpace.setPosition(720,0);
    if(!this->t1.loadFromFile("assets/imgs/towers/tower4.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower1.setTexture(t1);
    this->tower1.setPosition(720, 0);
    this->t1Cost=100;

    // for tower 2 freeze_tower
    if(!this->t2.loadFromFile("assets/imgs/towers/tower2.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower2.setTexture(t2);
    this->tower2.setPosition(920, 0);
    this->tower2.scale(sf::Vector2f(0.7,0.7));
    this->t2Cost=200;

    // for tower 3 bazooka_tower
    if(!this->t3.loadFromFile("assets/imgs/towers/tower1.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower3.setTexture(t3);
    this->tower3.setPosition(730, 200);
    this->tower3.scale(sf::Vector2f(0.778,0.778));
    this->t3Cost=300;

    // for tower 4 boat
    if(!this->t4.loadFromFile("assets/imgs/towers/boat.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower4.setTexture(t4);
    this->tower4.setPosition(920, 200);
    this->tower4.scale(sf::Vector2f(0.778,0.778));
    this->t4Cost=350;


    this->titleFont.loadFromFile("assets/fonts/Robus.otf");
    this->font.loadFromFile("assets/fonts/upheavtt.ttf");
    this->initButtons();
    drag.scale(sf::Vector2f(0.6,0.6));
    
    
}

GameStates::~GameStates(){
    for(auto i: waves){
        delete i;
    }

    for(auto i: towers){
        delete i;
    }
}

void GameStates::Update(const float& dt){
    this->updateMousePositions();
    this->updateInput(dt);
    map->Update();
    
    if  (!waves.empty()) {
        (waves.front())->Update(dt);
        if ((waves.front())->HasEnded()){
            waves.front()->~Wave();
            waves.erase(waves.begin());
        }
    } else {
        // this->quit = true;
        this->states->push(new EndGameState(this->window, this->states, "Victory"));
    }

    if (player->health <= 0) {
        // this->quit = true;
        this->states->push(new EndGameState(this->window, this->states, "Defeat"));
    }

    for(auto i: towers){
        i->Update(this->mousePosView, dt);
        //i->rotate(sf::Vector2i(this->enemies[0]->GetSprite().getPosition().x,this->enemies[0]->GetSprite().getPosition().y), this->enemies[0]->GetSprite().getPosition());
        i->enemieInRange(this->waves.front()->getCurEnemies());
        i->collisionDetect(this->waves.front()->getCurEnemies(), dt);
    }

    this->updateDrag();
    this->updateButttons(); 
    player->Update();
}

void GameStates::Render(RenderTarget * target){
    map->Render(window);

   

    this->window->draw(this->towerSpace);

    this->window->draw(this->tower1);
    this->window->draw(this->tower2);
    this->window->draw(this->tower3);
    this->window->draw(this->tower4);

    this->renderButtons(this->window);

    this->renderDrag();

    for(auto i: towers){
        i->Render(this->window);
    }

    if  (!waves.empty()) {
        (waves.front())->Render(this->window);
    }

    player->Render(this->window);

    // For visualising the mouse coordinates
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y-50);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    std::cout << ss.str() << std::endl;

    // added for debug
    //std::cout << this->towers.size() << std::endl;

}

void GameStates::updateInput(const float& dt){
}

void GameStates::endState(){
    std::cout << "Ending Game state" << '\n';
}


void GameStates::updateDrag(){
    // button presssed
    sf::Event event;
    while(this->window->pollEvent(event)){
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
            // tower type 1
            if(tower1.getGlobalBounds().contains(this->mousePosView)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    this->isPressed1 = true;
                }
            }
            if(tower2.getGlobalBounds().contains(this->mousePosView)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    this->isPressed2 = true;
                    
                }
            }
            if(tower3.getGlobalBounds().contains(this->mousePosView)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    this->isPressed3 = true;      
                }
            }
            if(tower4.getGlobalBounds().contains(this->mousePosView)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    this->isPressed4 = true;      
                }
            }
            break;
        case sf::Event::MouseButtonReleased:
            // it chrashes if placed on the gui
            if(isPressed1 && mousePosView.x<720 && mousePosView.y<720){
                if(!this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->getIsOccupied() && !this->map->GetTile(std::make_pair(this->mousePosView.y/48,this->mousePosView.x/48))->IsPath() && !this->map->GetTile(std::make_pair(this->mousePosView.y/48,this->mousePosView.x/48))->IsWater() && this->player->coins >=t1Cost){
                    this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->setIsOccupied();
                    int x = this->mousePosView.x/48;
                    int y = this->mousePosView.y/48;
                    this->towers.push_back(new GunTower("assets/imgs/towers/tower4.png",sf::Vector2f(x*48,y*48),sf::Vector2f(0.6,0.6)));
                    this->player->coins -= t1Cost;
                }
            }
            if(isPressed2 && mousePosView.x<720 && mousePosView.y<720){
                if(!this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->getIsOccupied() && !this->map->GetTile(std::make_pair(this->mousePosView.y/48,this->mousePosView.x/48))->IsPath() && !this->map->GetTile(std::make_pair(this->mousePosView.y/48,this->mousePosView.x/48))->IsWater() && this->player->coins >=t2Cost){
                    this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->setIsOccupied();
                    int x = this->mousePosView.x/48;
                    int y = this->mousePosView.y/48;
                    this->towers.push_back(new FreezeTower("assets/imgs/towers/tower2.png",sf::Vector2f(x*48,y*48),sf::Vector2f(0.6,0.6)));
                    this->player->coins -= t2Cost;
                }
            }
            if(isPressed3 && mousePosView.x<720 && mousePosView.y<720){
                if(!this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->getIsOccupied() && !this->map->GetTile(std::make_pair(this->mousePosView.y/48,this->mousePosView.x/48))->IsPath() && !this->map->GetTile(std::make_pair(this->mousePosView.y/48,this->mousePosView.x/48))->IsWater() && this->player->coins >=t3Cost){
                    this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->setIsOccupied();
                    int x = this->mousePosView.x/48;
                    int y = this->mousePosView.y/48;
                    this->towers.push_back(new BazookaTower("assets/imgs/towers/tower1.png",sf::Vector2f(x*48,y*48),sf::Vector2f(0.6,0.6)));
                    this->player->coins -= t3Cost;
                }
            }
            if(isPressed4 && mousePosView.x<720 && mousePosView.y<720){
                if(!this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->getIsOccupied() && this->map->GetTile(std::make_pair(this->mousePosView.y/48,this->mousePosView.x/48))->IsWater() && this->player->coins >=t3Cost){
                    this->map->GetTile(std::make_pair(this->mousePosView.x/48,this->mousePosView.y/48))->setIsOccupied();
                    int x = this->mousePosView.x/48;
                    int y = this->mousePosView.y/48;
                    this->towers.push_back(new BoatTower("assets/imgs/towers/boat.png",sf::Vector2f(x*48,y*48),sf::Vector2f(0.6,0.6), this->player));
                    this->player->coins -= t3Cost;
                }
            }
            this->isPressed1 = false;
            this->isPressed2 = false;
            this->isPressed3 = false;
            this->isPressed4 = false;
            break;
        case sf::Event::Closed:
            this->window->close();
            break;
        default:
            break;
        }
        break;
    } 
    if(this->isPressed1 || this->isPressed2 || this->isPressed3|| this->isPressed4){
        if(this->tower1.getGlobalBounds().contains(this->mousePosView)){
            drag.setTexture(*this->tower1.getTexture());
        }
        if(this->tower2.getGlobalBounds().contains(this->mousePosView)){
            drag.setTexture(*this->tower2.getTexture());
        }
        if(this->tower3.getGlobalBounds().contains(this->mousePosView)){
            drag.setTexture(*this->tower3.getTexture());
        }
        if(this->tower4.getGlobalBounds().contains(this->mousePosView)){
            drag.setTexture(*this->tower4.getTexture());
        }
        drag.setPosition(this->mousePosView.x, mousePosView.y);
        drag.setOrigin(sf::Vector2f(80 ,80));
    }
}

void GameStates::renderDrag(){
    if(this->isPressed1 || isPressed2 || isPressed3 || isPressed4){
        this->window->draw(drag);
    }
}

void GameStates::initButtons(){
    this->buttons["Quit"] = new Button(740, 650, 150, 50, "Quit", this->titleFont, sf::Color(70,70,70,200), sf::Color(150,150,150,255), sf::Color(20,20,20,200));
    this->buttons["tower1"] = new Button(740, 150, 100, 50, "100", this->font, sf::Color(70,70,70,0), sf::Color(70,70,70,0), sf::Color(70,70,70,0));
    this->buttons["tower2"] = new Button(940, 150, 100, 50, "200", this->font, sf::Color(70,70,70,0), sf::Color(70,70,70,0), sf::Color(70,70,70,0));
    this->buttons["tower3"] = new Button(740, 350, 100, 50, "300", this->font, sf::Color(70,70,70,0), sf::Color(70,70,70,0), sf::Color(70,70,70,0));
    this->buttons["tower4"] = new Button(940, 350, 100, 50, "350", this->font, sf::Color(70,70,70,0), sf::Color(70,70,70,0), sf::Color(70,70,70,0));
}

void GameStates::updateButttons(){
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->Update(this->mousePosView);
    }
    //Back to mainMenu
    if(this->buttons["Quit"]->isPressed()){
        this->quit=true;
    }
}


void GameStates::renderButtons(RenderTarget * target){
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->Render(target);
    } 
}