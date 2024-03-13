#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Character/Character.h"
#include "Combat/Action.h"


int main() {
    Player *player = new Player("Victor", 30, 7, 10, 5);
    Player *player2 = new Player("The Knight", 25, 15, 7, 10);
    Enemy *enemy = new Enemy("Punished Soul of Skeleton Prime", 40, 6, 8, 5, 10);
    Enemy *enemy2 = new Enemy("Punished Soul of The Destructor", 50, 10, 9, 5, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(player2);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete player2;
    delete enemy;
    delete enemy2;
    delete combat;
    return 0;
}
