#ifndef _FIELDCLASS_H
#define _FIELDCLASS_H

#include <string>
#include <vector>
#include "GameStateClass.h"
using namespace std;

class FieldClass {
  private:

  GameStateClass *gameState;

  public:
    vector<int> field;

    bool DoMove(int move, int playerId);

    bool UndoMove(int move);

    FieldClass(GameStateClass *_gameState);

    void UpdateField(string value);

    void PrintDebug();

    // x = 0 -> rows-1, zeilen-1
    // y = 0 -> columns-1, spalten-1
    inline void SetCellValue(int row, int column, int value){
        // Abfrage entfernt für optimierung Geschwindigkeit
        //if(row >= 0 && row < gameState->fieldRows){
        //  if(column >= 0 && gameState->fieldColumns){
        field[row * gameState->fieldColumns + column] = value;
        //}
    //}
        //return false;
    }

    // x = 0 -> rows-1, zeilen-1
    // y = 0 -> columns-1, spalten-1
    inline int GetCellValue(int row, int column){
        // Abfrage entfernt für optimierung Geschwindigkeit
        //if(row >= 0 && row < gameState->fieldRows){
        //  if(column >= 0 && gameState->fieldColumns){
                return field[row * gameState->fieldColumns + column];
            //}
        //}
        //return 0;
    }

};
#endif
