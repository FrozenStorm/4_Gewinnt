#include <iostream>
#include "ParserClass.h"
#include "BotClass.h"
#include "GameStateClass.h"

ParserClass::ParserClass(GameStateClass &_gameState, BotClass &_bot) : bot(_bot) , gameState(_gameState){

}

void ParserClass::Run() {
    clock_t startTime, endTime;
    while (true) {
        string command, subCommand, value;
        cin >> command;
        if(command == "settings"){
            cin >> subCommand;
            cin >> value;
            gameState.UpdateSettings(subCommand,value);
        }
        else if(command == "update"){
            cin >> command;
            if(command == "game"){
                cin >> subCommand;
                cin >> value;
                gameState.UpdateGame(subCommand,value);
            }
        }
        else if(command == "action"){
            cin >> subCommand;
            cin >> value;
            gameState.UpdateMove(subCommand,value);
            startTime = clock();
            bot.DoTurn();
            endTime = clock();
        }
        else if(command == "debug")
        {
            bot.PrintDebug();
            gameState.PrintDebug();
        }
        else if(command == "time"){
            cout << "StartTime = " << startTime * 1000 / CLOCKS_PER_SEC << " ms" << endl;
            cout << "EndTime = " << endTime  * 1000 / CLOCKS_PER_SEC << " ms" << endl;
            cout << "Elapsed time = " << (float)(endTime - startTime) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
        }
        else if(command == "tree"){
            bot.PrintTree();
        }
        else{
            cout << "unknown command" << endl;
        }
    }
}


