#include "BotClass.h"
#include "GameStateClass.h"
#include "ParserClass.h"
#include <iostream>
using namespace std;

BotClass *bot;

GameStateClass *gameState;

ParserClass *parser;

int main(int argc, char *argv[]) {
    gameState = new GameStateClass();
    bot = new BotClass(gameState);
    gameState->bot = bot;
    parser = new ParserClass(gameState, bot);
    parser->Run();

    delete parser;
    delete bot;
    delete gameState;
}

// graphviz


/* Test Code


settings timebank 10000

settings time_per_move 500

settings player_names player1,player2

settings your_bot player1

settings your_botid 1

settings field_columns 7

settings field_rows 6

Round 1

update game round 1

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0

action move 10000

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,1,0,0,0

Round 2

update game round 3

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0

action move 9775

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0

Round 3

update game round 5

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0

action move 8839

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,1,0,1,0,0,0

Round 4

update game round 7

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;2,1,0,1,0,0,0

action move 8396

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;2,1,0,1,1,0,0

Round 5

update game round 9

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;2,1,2,1,1,0,0

action move 8089

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,0,1,0,0,0;0,0,1,2,0,0,0;2,1,2,1,1,0,0

Round 6

update game round 11

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,2,1,0,0,0;0,0,1,2,0,0,0;2,1,2,1,1,0,0

action move 8162

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,2,1,0,0,0;0,1,1,2,0,0,0;2,1,2,1,1,0,0

Round 7

update game round 13

update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,2,0,0,0;0,0,2,1,0,0,0;0,1,1,2,2,0,0;2,1,2,1,1,0,0

action move 6827




*/
