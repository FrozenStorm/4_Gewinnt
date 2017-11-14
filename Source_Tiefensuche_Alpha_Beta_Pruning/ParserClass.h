#ifndef _PARSERCLASS_H
#define _PARSERCLASS_H

#include <time.h>
using namespace std;

class BotClass;
class GameStateClass;

class ParserClass {
public:
    /*!
    \brief Endlosschlaufe welche alle Eingaben (Befehle) der Game-Engine entgegennimmt und auswertet.
   */
    void Run();

    /*!
     \brief Konstruktor
     \param _gameState Referenz auf den Spielzustand
     \param _bot Referenz auf den Bot welcher die nächsten Spielzüge berechnet
    */
    ParserClass(GameStateClass &_gameState, BotClass &_bot);

private:
    BotClass &bot;                  // Referenz auf den Bot welcher die nächsten Spielzüge berechnet

    GameStateClass &gameState;      // Referenz auf den aktuellen Spielzustand

};
#endif
