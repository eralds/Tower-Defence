#include "wave.hpp"

Wave::Wave(std::string _name, int e1, int e2, int e3, int e4, int e5, std::pair<int, int> _startPos, Player* pl)
{
    startPos = _startPos;
    name = _name;
    std::cout << "starting wave " << name << std::endl; 

    //enemy type 5  5000 health   0.25 speed  140 size 500 coins
    for (size_t i = e5; i > 0; i--)
    {
        enemiesWaitlist.push_back(new Enemy(5,"assets/imgs/enemies/ship5.png", static_cast<float>(TILELEN * startPos.second), static_cast<float>(TILELEN*startPos.first), 5000, 0.20, 180, 40*(i-1), 500));      
    }
    //enemy type 4  200 health   1 speed  110 size 150 coins
    for (size_t i = 0; i < e4; i++)
    {
        enemiesWaitlist.push_back(new Enemy(4,"assets/imgs/enemies/ship4.png", static_cast<float>(TILELEN * startPos.second), static_cast<float>(TILELEN*startPos.first), 200, 0.75, 110, 4, 150));      
    }
    //enemy type 3  200 health   1.5 speed  100 size 100 coins
    for (size_t i = 0; i < e3; i++)
    {
        enemiesWaitlist.push_back(new Enemy(3,"assets/imgs/enemies/ship3.png", static_cast<float>(TILELEN * startPos.second), static_cast<float>(TILELEN*startPos.first), 200, 1, 100, 4, 100));      
    }
    //enemy  type 2 50 health   4 speed  80 size 50 coins
    for (size_t i = 0; i < e2; i++)
    {
        enemiesWaitlist.push_back(new Enemy(2,"assets/imgs/enemies/ship2.png", static_cast<float>(TILELEN * startPos.second), static_cast<float>(TILELEN*startPos.first), 50, 2, 80, 4, 50));      
    }
    //enem type 1  100 health   1 speed  80 size 25 coins
    for (size_t i = 0; i < e1; i++)
    {
        enemiesWaitlist.push_back(new Enemy(1,"assets/imgs/enemies/ship1.png", static_cast<float>(TILELEN * startPos.second), static_cast<float>(TILELEN*startPos.first), 100, 0.5, 80, 4, 25));      
    }

    this->font.loadFromFile("assets/fonts/upheavtt.ttf");
    this->text.setFont(this->font);
    this->text.setString(_name + "/5");
    this->text.setFillColor(Color::Black);
    this->text.setCharacterSize(30);
    this->text.setPosition(30,5);
    player = pl;
}

Wave::~Wave()
{
    for(auto i: enemies){
        delete i;
    }
    std::cout << "ending wave " << name << std::endl; 
}

void Wave::Update(const float& dt){
    if (!enemiesWaitlist.empty()){ 
        if (enemiesWaitlist.back()->GetWait() <= wait) {
            enemies.push_back(enemiesWaitlist.back());
            enemiesWaitlist.pop_back();
            wait = 0;
        } 
        wait += dt;
    } 

    for (auto i = this->enemies.begin(); i != enemies.end(); ){
        (*i)->Update();
        (*i)->UpdatePath();
        if((*i)->CheckEndOfPath()) {
            // std::cout << "removing element" << std::endl;
            (*i)->~Enemy();
            this->enemies.erase(i);
            player->health -= 1;
        }
        else if((*i)->CheckIfDead()){
            // std::cout << "removing element" << std::endl;
            player->coins += (*i)->GetReward();
            auto curEnemy = (*i);
            this->enemies.erase(i);
            switch (curEnemy->GetType()) {
                case 5:
                    for(int j = 0; j < 3; j++) {
                        auto e = new Enemy(3,"assets/imgs/enemies/ship3.png", static_cast<float>(curEnemy->GetPosition().x), static_cast<float>(curEnemy->GetPosition().y), 200, 0.9 + 0.2*j, 100, 0, 100);     
                        e->SetPath(this->path,curEnemy->GetCurTile(), curEnemy->GetDist());
                        enemiesWaitlist.push_back(e);
                    }
                    break;
                case 3:
                    for(int j = 0; j < 3; j++) {
                        auto e = new Enemy(1,"assets/imgs/enemies/ship1.png", static_cast<float>(curEnemy->GetPosition().x), static_cast<float>(curEnemy->GetPosition().y), 100, 0.4 + 0.2*j, 80, 0, 25);      
                        e->SetPath(this->path,curEnemy->GetCurTile(), curEnemy->GetDist());
                        enemiesWaitlist.push_back(e);
                    }
                    break;
            }
            curEnemy->~Enemy();
        } else {
            i++;
        }
    }
    // bullet animation
}

void Wave::Render(sf::RenderWindow* window){
    for (auto e : enemies){
        e->Render(window);
    }
    window->draw(this->text);
}

void Wave::SetPath(std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path) {
    path = _path;
    for (auto e : enemiesWaitlist){
        e->SetPath(_path,startPos.first*MAPDIM+startPos.second);
    }
}

bool Wave::HasEnded() {
    if (enemies.empty() && enemiesWaitlist.empty()) {
        return true;
    }
    return false;
}


std::vector<Enemy*> Wave::getCurEnemies(){
    return this->enemies;
}