#ifndef _RATINGCLASS_H
#define _RATINGCLASS_H

#include <iostream>
using namespace std;

class GameStateClass;

class RatingClass {
  public:

    /*!
     \brief Konstruktor
     \param _gameState Referenz auf den Spielzustand
    */
    RatingClass(GameStateClass &_gameState);

    /*!
     \brief Gibt die Bewertung der aktuellen Spielsituation in "gamestate.field" zurück wobei der Wert positiv ist wenn die Situation besser für den Spieler in "playerId" ist.
     \param playerId Spieler für welcher die Situation bewertet werden soll.
     \return Bewertung für den übergebenen Spieler in "playerId" wobei positiv für ihn gewinnbringen ist. Bewertung liegt immer im Bereich  -WINNIG_VALUE <= return value <= WINNIG_VALUE.
    */
    int32_t GetRating(int playerId);

    /*!
     \brief Ausgabe aller Attribute der Klasse in std::out
    */
    void PrintDebug();

  private:
    GameStateClass &gameState;      // Referenz auf den aktuellen Spielzustand

};
#endif
