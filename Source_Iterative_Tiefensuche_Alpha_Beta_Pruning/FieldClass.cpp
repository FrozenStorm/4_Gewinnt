#include <iostream>
#include <sstream>
#include "FieldClass.h"
#include "GameStateClass.h"


bool FieldClass::DoMove(int move, int playerId) {
    for(int x = gameState->fieldRows-1 ; x >= 0 ; x--){
        if(GetCellValue(x,move)==0){
            SetCellValue(x, move, playerId);
            return true;
        }
    }
    return false;
}

bool FieldClass::UndoMove(int move) {
    for(int x = 0 ; x < gameState->fieldRows ; x++){
        if(GetCellValue(x,move)!=0){
            SetCellValue(x, move, 0);
            return true;
        }
    }
    return false;
}

FieldClass::FieldClass(GameStateClass *_gameState) : gameState(_gameState) , field(_gameState->fieldColumns * _gameState->fieldRows, 0){
}


void FieldClass::UpdateField(string value){
    stringstream ss(value);
    string item;
    int cell;
    gameState->lastMove = -1;
    for(unsigned int i = 0; i < field.size(); i++) {
        if(((i+1)%gameState->fieldColumns == 0) && (i != 0)) getline(ss, item, ';');
        else getline(ss, item, ',');
        cell = stoi(item);
        if((cell != gameState->yourBotId) && (cell != 0)) cell = -gameState->yourBotId;       // Converting all non yourBotId player numbers to the negative value form yourBotId because of negamax calculations and tree generation
        if((cell != 0) && (field[i] == 0)) gameState->lastMove = i % gameState->fieldColumns; // If a cell has changed it was the move from the enemy
        field[i] = cell;
    }
}

void FieldClass::PrintDebug() {
    cout << "size: rows=" << gameState->fieldRows << " columns=" << gameState->fieldColumns << endl;
    cout << "field:" << endl;
    for(unsigned int i = 0; i < field.size(); i++) {
        if(((i+1)%gameState->fieldColumns == 0) && (i != 0)) cout << field[i] << ";" << endl;
        else cout << field[i] << ",";
    }
    cout << endl;
    cout << "x=2,y=0  =>  " << GetCellValue(2,0) << endl;
    cout << endl;
}
