#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Character/Character.h"
#include "Combat/Action.h"

// :)

int main() {
    Player *player = new Player(1,"Victor", 50, 100, 5, 5);
    Player *player2 = new Player(1, "The Knight", 50, 150, 7, 10);
    Enemy *enemy = new Enemy(100, "Skeleton Prime", 40, 50, 8, 5);
    Enemy *enemy2 = new Enemy(100, "The Destructor", 50, 50, 10, 9);

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
