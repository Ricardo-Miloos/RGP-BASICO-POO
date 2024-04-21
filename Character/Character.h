//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include <string>
#include <cmath>

using namespace std;

class Character {
protected:
    char name[30]{}; //Cambio de name de string a char[30]
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
public:
    Character(char *_name, int _health, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;
    //Funcion para volver la vida a 0 del objetivo
    virtual void setHealth(Character *target, int newHealth){ target->health = 0;};

    //TODO: Implementar metodo de defensa
    //Funcion para incrementar la defensa un 20% solo por el turno actual
    virtual void defend(Character *target){target->defense = ceil(target->defense * 1.2);};
    //Funcion para desactivar la defensa (volver la defensa a su valor original)
    virtual void stopDefend(Character *target){target->defense = floor(target->defense / 1.3);};
    //Funcion para saltar un turno y no hacer nada
    virtual void skipTurn(Character *target){};
    bool flee(Character* target);
    const char* getName();
    int getHealth();
    int getAttack();
    int getDefense();
    bool getIsPlayer();
    int getSpeed();
    string toString();
};


#endif //RPG_CHARACTER_H
