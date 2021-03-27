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

void Dungeon::handleLootActions(Room * room) {
    Item item = room->items.front();
    int  size = room->items.size();
    player.lootRoom(room);
    room->clearLoot();
    for (int i = 0; i < size; i++) {
        cout << "Has abierto un cofre y has encontrado un " << item.name << ".\n";     
        cout << "Tu salud es ahora" << player.currentHealth << ", tu ataque es ahora " << player.attack << " y tu defensa " << player.defence << ".\n";
    }
    
}

void Dungeon::handleRoomWithChest(Room * room) {
    cout << "Has entrado en una habitación con un gran tesoro...\n";
    string actions [] = {
        "a. Recoger el tesoro.",
        "b. Moverse a otra habitacion."
        };
    while (true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a") {
            handleLootActions(room);
            return;
        } else if (input == "b") {
            return;
        } else {
            cout << "Accion incorrecta \n";
        }   
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
        handleRoomWithChest(room);
    } else {
        handleEmptyRoom(room);
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