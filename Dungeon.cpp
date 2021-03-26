#include "Dungeon.h"
#include "Player.h"
#include <iostream>

Dungeon::Dungeon(Player p)
{
    player = p;
}

void Dungeon::printActions(int numActions, string actions[]) {
    cout << "Escoge una acción\n";
    for (int i = 0; i < numActions; i++) {
        cout << actions[i] << "\n";
    }
    
}

void Dungeon::handleEmptyRoom(Room * room) {
    cout << "Has entrado en una habitación pero esta vacia...\n";
    string actions [] = {"a. Moverse a otra habitacion."};
    while (true) {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "a") {
            return;
        } else {
            cout << "Accion incorrecta \n";
        }   
    }
}

void Dungeon::enterRoom(Room * room) {
    if (room->enemies.size() != 0) {
        // handle room with enemy
    } else if (room->items.size() != 0) {
        // handle room with chest
    } else {
        // handle empty room
    }
}

int Dungeon::runDungeon() {
    cout << "Bienvenido a la mazmorra, dentro encontrarás tesoros pero tambien a los enemigos que los protegen.\n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    while (true)
    {
        enterRoom(player.currentRoom);
    }
}