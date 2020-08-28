#pragma once
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include "entity.hpp"
#include <cmath>
#include "inventory.hpp"
#include "room.hpp"
#include <SFML/Audio.hpp>
class Inventory;
class Player : public Entity
{
public:

    Player() = delete;
    Player(sf::Texture&); 
    ~Player() {}

    //inventory management methods
    Inventory* GetInventory() { return inventory_; }
    void SetInventory(Inventory* inventory) { inventory_ = inventory; }

    //Getters for interfacing
    Room* GetRoom();

    void SetRoom(Room* r);

    sf::Sprite& GetSprite();
    float GetReload();

    bool CanDie() {if(immortal_ == 0) {return true;} else {return false;}}
    void Immortal() { immortal_ = 1;}
    void TakeDamage(int dmg);

    //sets reload time based on the current weapon
    void Attack();

    //input handling methods, determine behavior on player update
    void accUp(bool);
    void accLeft(bool);
    void accDown(bool);
    void accRight(bool);

    //hp & score access and management
    void SetHP(int hp) { hp_ = hp; }
    void AddHP(int hp);
    int GetHP() { return hp_; }
    int GetScore() { return score_; }
    void AddScore(int b) { score_ += b; }

    //Update methods
    void update(sf::Time dt);
    void Draw(sf::RenderWindow*, sf::Color c = sf::Color::Transparent);
    sf::Texture& GetTexture() { return texture_; }

    //difficulty handling
    int GetDifficulty() {return difficulty_;}
    void IncreaseDifficulty() { difficulty_ ++;}

private:
    //player's inventory
    Inventory* inventory_;
    //current room of the player
    Room* room_;

    //input handling
    bool accDown_;
    bool accUp_;
    bool accLeft_;
    bool accRight_;

    //for tracking reload rate
    float reload_;

    int hp_;
    int score_;
    int difficulty_;
    //for invincibility frames
    float immortal_;

    //graphics
    sf::Texture texture_;
    sf::Sprite sprite_;
};