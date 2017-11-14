#ifndef _PARSERCLASS_H
#define _PARSERCLASS_H

#include <time.h>
using namespace std;

class BotClass;
class GameStateClass;

class ParserClass {
public:
    void Run();
    ParserClass(GameStateClass *_gameState, BotClass *_bot);

private:
    BotClass *bot;

    GameStateClass *gameState;

};
#endif
