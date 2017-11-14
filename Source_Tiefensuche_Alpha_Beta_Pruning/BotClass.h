#ifndef _BOTCLASS_H
#define _BOTCLASS_H


#include "NodeClass.h"
#include "RatingClass.h"
using namespace std;

class GameStateClass;


class BotClass {
  public:
    /*!
     \brief Berechnet den nächsten Zug und gibt den Befehl für den Zug in std::out aus. "place_disc i" wobei i die Spaltennummer ist oder "no_moves" falls kein Zug berechnet werden konnte.
    */
    void DoTurn();


  private:
    GameStateClass &gameState;      // Referenz auf den aktuellen Spielzustand

    /*!
     \brief Berechnet rekursive den ganzen Baum mithilfe einer Tiefensuche um alle möglichen Spielverläufe zu evaluieren. Für jeden Knoten wird jeweils die Bewertung mit der RatingClass gemacht und die beste Zugmöglichkeit evaluiert.
     \param currentNode Pointer auf den Knoten für welcher die Nachfolgeknoten (Spielsitutationen) errechnet werden soll.
     \return Der Bewertungswert des Knoten anhand der Nachfolgeknoten.
    */
    int32_t GenerateSubtree(NodeClass *currentNode);


  public:
    /*!
     \brief Konstruktor
     \param _gameState Referenz auf den Spielzustand
     \param _maxDepth Maximale Tiefe für die Tiefensuche
    */
    BotClass(GameStateClass &_gameState, int _maxDepth);

    /*!
     \brief Destruktor
    */
    ~BotClass();

    /*!
     \brief Gibt die gesamte Baumstruktur der letzten berechnung für einen Zug in die Datei "treeView.gv" im Graphviz Format aus.
    */
    void PrintTree();

    /*!
     \brief Ausgabe aller Attribute der Klasse in std::out
    */
    void PrintDebug();


  private:
    int maxDepth;                       // Maximale Tiefe bis zu welcher gerechnet werden soll bei der Tiefensuche

    NodeClass *treeHead = nullptr;      // Pointer auf die Wurzel des Baumes für die Tiefensuche

    RatingClass rating;                 // Objekt der Ratingklasse welches das Bewerten lassen einer Spielsituation ermöglicht
};
#endif
