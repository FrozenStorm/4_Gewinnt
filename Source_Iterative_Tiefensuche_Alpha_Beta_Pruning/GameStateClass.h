#ifndef _GAMESTATECLASS_H
#define _GAMESTATECLASS_H

#include <time.h>
#include <vector>
#include <string>
using namespace std;

class FieldClass;
class BotClass;

//#define DEBUG

#define WINNIG_VALUE 1000000000

class GameStateClass {

public:
    BotClass *bot = nullptr;

    clock_t startTime = 0;

    clock_t endTime = 0;

    int timebank = 0;

    int timePerMove = 0;

    int playerCount = 0;

    vector<string> playerNames;

    string yourBotName = "";

    int yourBotId = 0;

    int fieldColumns = 0;

    int fieldRows = 0;

    int round = 0;

    int lastMove = -1;

    ~GameStateClass();

    void UpdateSettings(string key, string value);

    void UpdateGame(string key, string value);

    void UpdateMove(string key, string value);

    void PrintDebug();

    FieldClass *field = nullptr;
};
#endif
