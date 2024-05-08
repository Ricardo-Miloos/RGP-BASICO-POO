//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(int _experience, char* _name, int _health, int _attack, int _defense, int _speed) : Character(_experience,_name, _health, _attack, _defense, _speed,false) {
    experience = _experience;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int contador_defensa = 0;
    //Si la vida del enemigo es menor al 15% de su vida total, incrementar la defensa un 20%
    if(health < (health * 0.15) && contador_defensa == 0){
        defend(this);
        int trueDamage = damage - defense;
        if (trueDamage < 0 || defense > trueDamage) {
            trueDamage = 0;
        }
        contador_defensa++;
        if(health <= 0) {
            // Si la vida del enemigo es menor a 0 usar la funcion setHealth para que la vida sea 0
            setHealth(this, 0);
            cout << name << " has been defeated!" << endl;
            cout << "Life: 0" << endl;
        } else {
        cout << name << " took " << trueDamage << " damage!" << endl;
        cout << "Remaining health: " << health << endl;}
    }
    //Si la vida del enemigo no es mayor al 15% de su vida total, no incrementar la defensa
    else{
        int trueDamage = damage - defense;
        health-= trueDamage;;
        if(health <= 0) {
            // Si la vida del enemigo es menor a 0 usar la funcion setHealth para que la vida sea 0
            setHealth(this, 0);
            cout << name << " has been defeated!" << endl;
            cout << "Life: 0" << endl;
        } else {
            cout << name << " took " << trueDamage << " damage!" << endl;
            cout << "Remaining health: " << health << endl;
        }
    }
}


Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;
    Character* target = nullptr;
    for(auto character : possibleTargets) {
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player*> partyMembers) {
    Action currentAction;
    currentAction.speed = getSpeed();

    Character* target = selectTarget(partyMembers);
    currentAction.target = target;
    currentAction.action = [this, target](){
        doAttack(target);
    };

    return currentAction;
}