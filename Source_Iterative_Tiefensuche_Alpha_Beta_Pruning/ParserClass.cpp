#include <iostream>
#include "ParserClass.h"
#include "BotClass.h"
#include "GameStateClass.h"

ParserClass::ParserClass(GameStateClass *_gameState, BotClass *_bot) : bot(_bot) , gameState(_gameState){

}

void ParserClass::Run() {
    while (true) {
        string command, subCommand, value;
        cin >> command;
        if(command == "settings"){
            cin >> subCommand;
            cin >> value;
            gameState->UpdateSettings(subCommand,value);
        }
        else if(command == "update"){
            cin >> command;
            if(command == "game"){
                cin >> subCommand;
                cin >> value;
                gameState->UpdateGame(subCommand,value);
            }
        }
        else if(command == "action"){
            cin >> subCommand;
            cin >> value;
            gameState->UpdateMove(subCommand,value);
            gameState->startTime = clock();
            bot->DoTurn();
            gameState->endTime = clock();
        }
        else if(command == "debug")
        {
            bot->PrintDebug();
            gameState->PrintDebug();
        }
        else if(command == "time"){
            cout << "maxDepth = " << bot->maxDepth << endl;
            cout << "StartTime = " << gameState->startTime << " ms" << endl;
            cout << "EndTime = " << gameState->endTime << " ms" << endl;
            cout << "Elapsed time = " << (float)(gameState->endTime - gameState->startTime) << " ms" << endl;
        }
        else if(command == "tree"){
            bot->PrintTree();
        }else if(command == "path"){
            bot->PrintPath();
        }
        else{
            cout << "unknown command" << endl;
        }
    }
}


