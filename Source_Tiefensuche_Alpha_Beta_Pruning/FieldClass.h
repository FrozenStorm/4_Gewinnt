#ifndef _FIELDCLASS_H
#define _FIELDCLASS_H

#include <string>
#include <vector>
#include "GameStateClass.h"
using namespace std;

class FieldClass {
  private:

  GameStateClass &gameState; // Referenz auf den aktuellen Spielzustand

  public:
    vector<int> field;      // Spielfeld

    /*!
     \brief Fügt dem Spielfeld einen Stein für einen Spieler hinzu falls dies möglich ist
     \param move Spalte in welche gesetzt werden soll
     \param playerId Id des Spielers für welchen ein Stein platziert werden soll
     \return true für gültig, false für Fehler
    */
    bool DoMove(int move, int playerId);

    /*!
     \brief Entfernt dem Spielfeld einen Stein in der angegebenen Spalte
     \param move Spalte von welcher der oberste Stein entfernt werden soll
     \return true für gültig, false für Fehler
    */
    bool UndoMove(int move);

    /*!
     \brief Konstruktor
     \param _gameState Referenz auf den Spielzustand
    */
    FieldClass(GameStateClass &_gameState);

    /*!
     \brief Ausgabe aller Attribute der Klasse in std::out
    */
    void PrintDebug();

    /*!
     \brief Aktuallisiert das Spielfeld mit den gegebenen Werten
     \param value Spielfeld als string in der Form 0,0,0,1,2,0;0,0,0,1,1,2;..............
    */
    void UpdateField(string value);

    /*!
     \brief Setzt einen Stein an einer bestimmten Stelle im Spielfeld
     \param row Zeile (nullbasiert)
     \param column Spalte (nullbasiert)
     \param value Wert
    */
    inline void SetCellValue(int row, int column, int value){
        // Abfrage entfernt für optimierung der Geschwindigkeit
        //if(row >= 0 && row < gameState->fieldRows){
        //  if(column >= 0 && gameState->fieldColumns){
        field[row * gameState.fieldColumns + column] = value;
        //}
    //}
        //return false;
    }

    /*!
     \brief Gibt den Wert des Spielfeldes an einer bestimmten Stelle zurück
     \param row Zeile (nullbasiert)
     \param column Spalte (nullbasiert)
     \return Wert an dieser Stelle
    */
    inline int GetCellValue(int row, int column){
        // Abfrage entfernt für optimierung der Geschwindigkeit
        //if(row >= 0 && row < gameState->fieldRows){
        //  if(column >= 0 && gameState->fieldColumns){
                return field[row * gameState.fieldColumns + column];
            //}
        //}
        //return 0;
    }

};
#endif
