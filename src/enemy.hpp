#ifndef TD_ENEMY_HPP
#define TD_ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>
#include <stdlib.h> 
#include "const.h"


using namespace sf;

class Enemy {
    private:
        Texture texture;
        Sprite sprite;
        Vector2f position;

        int health;
        int maxHealth;
        RectangleShape healthBar;
        RectangleShape healthLeft;

        float yVelocity = 0;
        float xVelocity = 0;
        float distanceTraveled = 0;
        float speed;
        float originalSpeed;

        std::map<int ,std::vector<std::pair<int,DIRECTION>>> *path;
        int tile; 
        int tileNr = 0;
        int nextTile;
        int dir = IDLE;

        float size;
        int wait;
        int reward;
        int type;
        
    public:
        Enemy(int _type, std::string _path, float x, float y, int _health, float _speed, float _size, int _wait, int _reward);
        ~Enemy();
        void Update();
        void Render(RenderWindow *window);
        void SetSprite(std::string path);
        Sprite GetSprite();
        void SetPath( std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path, int startPos);
        void SetPath(std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path, int startPos,int dist);
        void UpdatePath();
        bool CheckEndOfPath();
        bool CheckIfDead();
        void GetHit(int damage);
        void InitHealthBar(float, float);
        void CheckDirection();
        int GetWait();
        int GetTileNr(); //see how far the enemy has gone
        int GetReward();

        // for debugging
        int getHealth(){return health;}

        // for freeze_tower
        float getOriginalSpeed();
        void setSpeed(float newSpeed);
        const int GetType();
        sf::Vector2f GetPosition();
        int GetCurTile();
        int GetDist();
        void SetFrozenEffect();
        void RemoveFrozenEffect();
};


#endif 