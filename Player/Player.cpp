//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}
// Si la defensa del jugador es mayor al daño recibido, no afecta la vida
void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (trueDamage < 0) {
        trueDamage = 0;
    } else {
        health -= trueDamage;
    }

    cout << name << " took " << trueDamage << " damage!" << endl;

    if(health <= 0) {
        cout << name << " has been killed!" << endl;
        // Si la vida del jugador es menor a 0 usar la funcion setHealth para que la vida sea 0
        setHealth(this, 0);
    }
    cout << "(Health remaining: " << health << ")" << endl;
}

void Player::levelUp() {
    level++;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {

    int action = 0;
    //Implementacion de un interruptor para validar la entrada desde la consola
    bool check = true;
    do {
        cout << getName() << " turn to act." << endl;
        cout << "Select an action: " << endl << "1. Attack" << endl;
        cout << "2. Defend" << endl;
        cin >> action;
        if(action == 1 || action == 2){
            check = false;
        }
        else {
            cout << "Invalid action" << endl;
        }
    }while (check);
        Action currentAction;
        Character* target = nullptr;

    switch(action) {
        case 1:
            if (defensas == 1) {
                stopDefend(this);
                cout << name << "Is switching to attack" << endl;
                defensas = 0;
            }
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target]() {
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            cout << name << " is attacking " << target->getName() << "!" << endl;
            break;
        case 2:
            currentAction.target = this;
            if (this->defensas == 0) {
                this->defend(this);
                cout << name << " is defending!" << endl;
                // Mostrar la defensa actualizada
                cout << "Defense: " << defense << endl;
                this->defensas++;
                currentAction.speed = getSpeed() * (100);
                currentAction.action = [this]() {
                    this->defend(this);
                };
            } else if (this->defensas == 1) {
                this->stopDefend(this);
                cout << name << " Is already om defend mode" << endl;
                cout << "Defense: " << defense << endl;
                this->defensas = 2;
                currentAction.speed = getSpeed() * (100);
                currentAction.action = [this]() {
                    this->stopDefend(this);
                };
            } else {
                cout << "Cant defend twice. You lose an action" << endl;
                this->skipTurn(this);
                //Take a movement from the player
                currentAction.speed = getSpeed() * (100);
                currentAction.action = [this]() {
                    this->skipTurn(this);
                };
                break;
                default:
                    cout << "Invalid action" << endl;
                break;
            }
    }
    cout << "\n";
    return currentAction;
}