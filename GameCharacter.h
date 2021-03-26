#include <string>

using namespace std;

class GameCharacter
{

public:
    string name;
    int maxHealth, currentHealth, attack, defence;
    GameCharacter(string, int, int, int);
    int takeDamage(int);
    bool checkIsDead();
};