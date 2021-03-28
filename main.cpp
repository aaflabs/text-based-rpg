#include <iostream>
#include "Dungeon.cpp"
#include "Player.cpp"
#include "GameCharacter.cpp"
#include "Item.cpp"
#include "Room.cpp"

int main()
{
    cout << "Saludos, ¿cuál es su nombre? \n";
    string playerName;
    cin >> playerName;
    Player player = Player(playerName, 100, 20, 10);

    Room firstRoom = Room(0, false, vector<Item>(), vector<GameCharacter>());
    
    Item sword = Item("Espada", 0, 20, 0);
    vector<Item> secondRoomItems;
    secondRoomItems.push_back(sword);
    Room secondRoom = Room(1, false, secondRoomItems, vector<GameCharacter>());

    GameCharacter firstEnemy = GameCharacter("Goblin", 50, 15, 5);
    vector<GameCharacter> thirdRoomEnemies;
    thirdRoomEnemies.push_back(firstEnemy);
    Room thirdRoom = Room(2, false, vector<Item>(), thirdRoomEnemies);

    GameCharacter secondEnemy = GameCharacter("Troll", 100, 20, 10);
    vector<GameCharacter> fourthRoomEnemies;
    fourthRoomEnemies.push_back(secondEnemy);
    Room fourthRoom = Room(3, true, vector<Item>(), fourthRoomEnemies);

    Dungeon dungeon = Dungeon(player);
    dungeon.rooms[0] = firstRoom;
    dungeon.rooms[1] = secondRoom,
    dungeon.rooms[2] = thirdRoom;
    dungeon.rooms[3] = fourthRoom;

    while (true) {
        int result = dungeon.runDungeon();
        if (result == 0) {
            break;
        }
    }

    cout << "Hasta luego.\n";    
}