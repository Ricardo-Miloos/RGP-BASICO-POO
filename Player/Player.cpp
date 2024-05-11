//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include <fstream>
#include "../GameInfo/FileHandler.h"

using namespace std;

//A
void Player::saveProgress() {
    char* buffer = this->serialize();
    FileHandler fileHandler = FileHandler();

    fileHandler.writeToFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
}

using namespace std;

Player::Player(int _experience, char* _name, int _health, int _attack, int _defense, int _speed) : Character(_experience, _name, _health, _attack, _defense, _speed,true) {
    level = 1;
    experience = 1;
}
Player::Player(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience) : Character(_experience, _name, _health, _attack, _defense, _speed, _isPlayer) {
    level = _level;
    experience = _experience;
}
int Player::getLevel() const {
    return level;
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
//fucion para subir de nivel al jugador
void Player::levelUp(Character *target) {
    while (this->experience >= 100) {
        level++;

        cout << "\n[" << name << " has leveled up to level: " << level << " !]" << endl;
        experience -= 100;
        cout << "\n(----- Choose a stat to upgrade it: -----)" << endl;
        cout << "1. Health" << endl;
        cout << "2. Attack" << endl;
        cout << "3. Defense" << endl;
        cout << "4. Speed" << endl;
        int stat = 0;
        while (stat < 1 || stat > 4) {
            cin >> stat;
            switch (stat) {
                case 1:
                    health += 10;
                    cout << "///[New Health: " << health << "]///" << endl;
                    break;
                case 2:
                    attack += 5;
                    cout << "///[New Attack: " << attack << "]///" << endl;
                    break;
                case 3:
                    defense += 5;
                    cout << "///[New Defense: " << defense << "]///" << endl;
                    break;
                case 4:
                    speed += 5;
                    cout << "///[New Speed: " << speed << "]///" << endl;
                    break;
                default:
                    cout << "Invalid stat" << endl;
                    break;
            }
        }
    }
//Preguntar si se quiere guardar el progreso
    cout << "Do you want to save your progress?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    int save = 0;
    while (save < 1 || save > 2) {
        cin >> save;
        switch (save) {
            case 1:
                saveProgress();
                break;
            case 2:
                cout << "Progress not saved" << endl;
                break;
            default:
                cout << "Invalid option" << endl;
                break;
        }

    }
}
void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp(this);
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
                cout << name << " Is switching to attack" << endl;
                defensas = 0;
            }
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target]() {
                doAttack(target);
                int enemy_exp = target->getExperience();
                if (target->getHealth() <= 0) {
                    cout << "You defeated " << target->getName() << "!" << endl;
                    gainExperience(enemy_exp);
                }
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
                cout << "Cannot defend twice. You lose an action" << endl;
                this->skipTurn(this);
                //Take a movement from the player
                currentAction.speed = getSpeed() * (100);
                currentAction.action = [this]() {
                    this->skipTurn(this);
                };
                break;
                default:
                    cout << "Invalid action, wait for the next turn." << endl;
                break;
            }

    }


    cout << "\n";
    return currentAction;
}
//A
char* Player::serialize() {
    char* iterator = buffer;

    memcpy(iterator, &name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &speed, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator, &isPlayer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator, &level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator, &experience, sizeof(experience));

    return buffer;
}

Player* Player::unserialize(char* buffer) {
    char* iterator = buffer;
    char name[30];
    int health, attack, defense, speed, level, experience;
    bool isPlayer;

    memcpy(&name, iterator, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator += sizeof(health);

    memcpy(&attack, iterator, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense, iterator, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&speed, iterator, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name, health, attack, defense, speed, isPlayer, level, experience);
}