#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Character/Character.h"
#include "Combat/Action.h"
#include "GameInfo/FileHandler.h"


Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(int error) {
        // Si no se encuentra la informacion del jugador, se pide al usuario que ingrese su nombre
        cout << "Could not find the player info, please enter your nickname: ";
        string name;
        cin >> name;
        cout << "Welcome " << name << "!" << endl;
        cout << "Is your player offensive or defensive? (1. OF/2. DEF): ";
        char type;
        cin >> type;
        if (type == '1') {
            cout << "Creating new offensive player..." << endl;
            return new Player((char*)name.c_str(), 100, 30, 5, 5, true, 1, 0);
        } else if (type == '2') {
            cout << "Creating new defensive player..." << endl;
            return new Player((char*)name.c_str(), 100, 20, 15, 5, true, 1, 0);
        } else {
            cout << "Creating default player..." << endl;
            return new Player((char*)name.c_str(), 100, 20, 10, 10, true, 1, 0);
        }
    }
}


// :)

int main() {
    srand(time(NULL)); // semilla para el generador de números aleatorios
   // Player *player = new Player(0,"Victor", 50, 30, 5, 5);
   // Player *player2 = new Player(0, "The Knight", 50, 150, 7, 10);
    Player *player = loadPlayerInfo();
    cout << player->getName() << endl;
    cout << player->toString() << endl;
    Enemy *enemy = new Enemy(100, "Skeleton Prime", 30, 0, 8, 5);
    Enemy *enemy2 = new Enemy(100, "The Destructor", 20, 1, 10, 9);

    vector<Character*> participants;

    participants.push_back(player);
    //participants.push_back(player2);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
   // delete player2;
    delete enemy;
    delete enemy2;
    delete combat;
    return 0;
}
