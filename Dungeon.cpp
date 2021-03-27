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

void Dungeon::handleFightActions(GameCharacter * enemy) {
    string actions [] = {
        "a. Atacar",
        "b. Retirarse"
        };
    while (true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a") {
            int damage = enemy->takeDamage(player.attack);
            cout << "Tu ataque hace " << damage << " de daño. \n";
        } else if (input == "b") {
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        } else {
            cout << "Accion incorrecta \n";
        }

        if (enemy->checkIsDead())  {
            cout << "Has ganado, tu enemigo " << enemy->name << " ha sido derrotado  \n";
            player.increaseStats(10, 5, 5);
            player.currentRoom->clearEnemies();
            return;
        }

        int damage = player.takeDamage(enemy->attack);
        cout << "El ataque de tu enemigo " << enemy->name << " hace " << damage << " de daño. \n";
        cout << "Ahora tu salud es " << player.currentHealth << ". \n";
        if (player.checkIsDead()) {
            return;
        }
    }
}

void Dungeon::handleRoomWithEnemy(Room * room) {
    GameCharacter enemy = room->enemies.front();
    cout << "Has entrado en una habitación y ves un..." << enemy.name << "\n";
    string actions [] = {
        "a. Pelear contra " + enemy.name,
        "b. Moverse a la habitacion anterior."
        };
    while (true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a") {
            handleFightActions(&enemy);
        } else if (input == "b") {
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        } else {
            cout << "Accion incorrecta \n";
        }   
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

void Dungeon::handleMovementActions(Room * room) {
    while (true) {
        if (room->pos == 0) {
            string actions[] = {"a. Move right", "b. Move down"};
            printActions(2, actions);
            string input;
            cin >> input;
            if (input == "a") {
                player.changeRooms(&rooms[1]);
            } else if (input == "b") {
                player.changeRooms(&rooms[2]); 
            } else {
                cout << "Accion incorrecta \n";
            }
        } else if (room->pos == 1) {
            string actions[] = {"a. Move left"};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "a") {
                player.changeRooms(&rooms[0]);
            } else {
                cout << "Accion incorrecta \n";
            }

        } else if (room->pos == 2) {
            string actions[] = {"a. Move up", "b. Move right"};
            printActions(2, actions);
            string input;
            cin >> input;
            if (input == "a") {
                player.changeRooms(&rooms[0]);
            } else if (input == "b") {
                player.changeRooms(&rooms[3]); 
            } else {
                cout << "Accion incorrecta \n";
            }
            
        } else {
            string actions[] = {"a. Move left"};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "a") {
                player.changeRooms(&rooms[2]);
            } else {
                cout << "Accion incorrecta \n";
            }
        }
    }
}

void Dungeon::enterRoom(Room * room) {
    if (room->enemies.size() != 0) {
        handleRoomWithEnemy(room);
    } else if (room->items.size() != 0) {
        handleRoomWithChest(room);
    } else {
        handleEmptyRoom(room);
    }
}

int Dungeon::performEndGameLogic() {
    string actions[] = {"a. Yes", "b. No"};
    while (true)
    {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a") {
            return 1;
        } else if (input == "b") {
            return 0;
        } else {
            cout << "Accion incorrecta \n";
        }       
    }   
}

int Dungeon::runDungeon() {
    cout << "Bienvenido a la mazmorra, dentro encontrarás tesoros pero tambien a los enemigos que los protegen.\n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    while (true)
    {
        enterRoom(player.currentRoom);
        if (player.checkIsDead()) {
            cout << "Game over, jugar otra partida?\n";
            return performEndGameLogic();
        } else {
            if (player.currentRoom->isExit) {
                if (player.currentRoom->enemies.size() == 0) {
                    cout << "Has ganado, jugar otra partida?\n";
                    return performEndGameLogic();
                }
            }
        }
        handleMovementActions(player.currentRoom);
    }
}