#include "player.hpp"

Player::Player()
{
    this->font.loadFromFile("assets/fonts/upheavtt.ttf");
    this->healthText.setFont(this->font);
    this->healthText.setFillColor(sf::Color::Black);
    this->healthText.setCharacterSize(30);
    

    this->coinsText.setFont(this->font);
    this->coinsText.setFillColor(sf::Color::Black);
    this->coinsText.setCharacterSize(30);


    healthText.setString("Health: " + std::to_string(health));
    coinsText.setString("Coins: " + std::to_string(coins));
    this->coinsText.setPosition(TILELEN*15 - 200,5);
    this->healthText.setPosition(TILELEN*15 - 200,40);
}

void Player::Update()
{
    healthText.setString("Health: " + std::to_string(health));
    coinsText.setString("Coins: " + std::to_string(coins));
}

void Player::Render(sf::RenderWindow* window)
{
    window->draw(this->healthText);
    window->draw(this->coinsText);
}

