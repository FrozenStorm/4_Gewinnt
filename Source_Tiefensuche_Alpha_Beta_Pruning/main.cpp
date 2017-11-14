#include "BotClass.h"
#include "GameStateClass.h"
#include "ParserClass.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    GameStateClass gameState;
    BotClass bot(gameState,7);              // max 7 for a timepermove=500 and timebank=10000
    ParserClass parser(gameState, bot);
    parser.Run();
}

/* Test Inputs


settings timebank 10000
settings time_per_move 500
settings player_names player1,player2
settings your_bot player1
settings your_botid 1
settings field_columns 7
settings field_rows 6
update game round 3
update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,1,2,0,0,0
debug
action move 10000
time
tree
debug


settings timebank 10000
settings time_per_move 500
settings player_names player1,player2
settings your_bot player1
settings your_botid 1
settings field_columns 7
settings field_rows 6
update game round 12
update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,1;0,0,0,0,0,0,2;0,0,0,0,0,0,2;1,1,1,0,0,0,2
debug
action move 10000
time
debug

settings timebank 10000
settings time_per_move 500
settings player_names player1,player2
settings your_bot player1
settings your_botid 1
settings field_columns 7
settings field_rows 6
update game round 12
update game field 0,0,0,0,0,0,0;0,0,2,2,0,0,0;0,0,2,1,0,0,0;0,0,1,1,0,0,0;0,1,1,2,0,0,0;0,1,2,1,2,0,0
debug
action move 10000
time
tree
debug



settings timebank 10000
settings time_per_move 500
settings player_names player1,player2
settings your_bot player1
settings your_botid 1
settings field_columns 7
settings field_rows 6
update game round 13
update game field 0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,0,0,0,0,0;0,0,1,2,0,0,0;1,0,1,1,2,0,0;2,2,2,1,1,0,2
debug
action move 10000
time
tree
debug
*/
