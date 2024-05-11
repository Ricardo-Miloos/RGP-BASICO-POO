//
// Created by Victor Navarro on 15/02/24.
//
#pragma once
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>

class Enemy;

class Player: public Character {
    //TODO: Implement Classes (Mage, Warrior, Rogue, etc..)
    //TODO: Implement Inventory

private:
    int level = 1;
    void levelUp(Character *target);
public:
    Player(int _experience, char* _name, int _health, int _attack, int _defense, int _speed);
    Player(char* _name, int _health, int _attack, int _defense, int _speed, bool isPlayer, int _level, int _experience);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    int getLevel() const; // Método para obtener el nivel del jugador
    Character* selectTarget(vector<Enemy*> possibleTargets);
    Action takeAction(vector<Enemy*> enemies);
    int defensas = 0;
    void gainExperience(int exp);
    char* serialize();
    static Player* unserialize(char* buffer);


    static const unsigned int BUFFER_SIZE = sizeof (name) + sizeof(health) + sizeof(attack) + sizeof(defense) + sizeof(speed) + sizeof(isPlayer) + sizeof(level) + sizeof(experience);

private:

    char buffer[Player::BUFFER_SIZE];

    void saveProgress();

};


#endif //RPG_PLAYER_H

    //TODO: Implement use object


