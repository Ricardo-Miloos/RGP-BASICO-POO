//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
Character::Character(int _experience, char *_name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    //Cambio de name de string a char[30]
    for (int i = 0; i < 30; i++) {
        name[i] = _name[i];
    }
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    experience = _experience;
}

const char* Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}
int Character::getExperience() {
    return experience;
}
//check
string Character::toString() {
    return "Name: " + string (name) + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed ) + "\nExperience: " + to_string(experience) + "\n";
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}
