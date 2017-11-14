#include <iostream>
#include <sstream>
#include <algorithm>
#include "GameStateClass.h"
#include "FieldClass.h"

GameStateClass::~GameStateClass(){
    delete field;
}

void GameStateClass::UpdateSettings(string key, string value) {
    if(key == "timebank"){
        timebank = stoi(value);
    }
    if(key == "time_per_move"){
        timePerMove = stoi(value);
    }
    if(key == "player_names"){
        playerNames.clear();
        stringstream ss(value);
        string item;
        while(getline(ss, item, ',')){
            playerNames.push_back(item);
        }
    }
    if(key == "your_bot"){
        yourBotName = value;
    }
    if(key == "your_botid"){
        yourBotId = stoi(value);
    }
    if(key == "field_columns"){
        fieldColumns = stoi(value);
    }
    if(key == "field_rows"){
        fieldRows = stoi(value);
    }
}

void GameStateClass::UpdateGame(string key, string value) {
    if(key == "round"){
        round = stoi(value);
    }
    if(key == "field"){
        if(field == NULL) field = new FieldClass(*this);
        field->UpdateField(value);
    }
}

void GameStateClass::UpdateMove(string key, string value) {
    if(key == "move"){
        timebank = stoi(value);
    }
}

void GameStateClass::PrintDebug() {
#ifdef DEBUG
    cout << "Debug Mode" << endl;
#ifdef USE_ALPHA_BETA
    cout << "Using NegaMax with Alpha Beta" << endl;
#else
    cout << "Using NegaMax" << endl;
#endif
#endif

    cout << "timebank = " << timebank << endl;
    cout << "timePerMove = " << timePerMove << endl;
    cout << "playerCount = " << playerCount << endl;
    cout << "playerNames = ";
    for_each(playerNames.begin(), playerNames.end(), [](string name){cout << name << ",";});
    cout << endl;
    cout << "yourBotName = " << yourBotName << endl;
    cout << "yourBotId = " << yourBotId << endl;
    cout << "fieldColumns = " << fieldColumns << endl;
    cout << "fieldRows = " << fieldRows << endl;
    cout << "round = " << round << endl;
    cout << endl;
    if(field != NULL) field->PrintDebug();
}
