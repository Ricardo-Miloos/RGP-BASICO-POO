//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(int _experience, char* _name, int _health, int _attack, int _defense, int _speed) : Character(_experience,_name, _health, _attack, _defense, _speed,false) {
    experience = _experience;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

// Aumentar el nivel del enemigo
void Enemy::levelUp() {
        level++;
        // Generar incrementos aleatorios para las estadísticas del enemigo al subir de nivel
        int healthIncrease = rand() % 10 + 1;
        int attackIncrease = rand() % 2 + 1;
        int defenseIncrease = rand() % 5 + 1;
        int speedIncrease = rand() % 5 + 1;

        // Aumentar las estadísticas
        health += healthIncrease;
        attack += attackIncrease;
        defense += defenseIncrease;
        speed += speedIncrease;

        cout << "[ Warning! " << name << " has leveled up to level " << level << "! ]" << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defense: " << defense << endl;
        cout << "Speed: " << speed << endl;
        cout << "\n" << endl;
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
            //cout << "Life: 0" << endl;
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
    //target con la menor vida
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
    // Obtener el nivel actual del jugador
    int playerLevel = partyMembers[0]->getLevel();

    // Verificar si el nivel del jugador ha aumentado
    if (playerLevel > level) {
        // Subir de nivel al enemigo
        levelUp();
    }

    Action currentAction;
    currentAction.speed = getSpeed();
    Character* target = selectTarget(partyMembers);
    currentAction.target = target;
    currentAction.action = [this, target](){
        doAttack(target);
    };

    return currentAction;
}

