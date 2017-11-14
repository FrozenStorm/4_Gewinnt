#ifndef _BOTCLASS_H
#define _BOTCLASS_H

#include "NodeClass.h"
#include "RatingClass.h"
using namespace std;

class GameStateClass;


class BotClass {
  public:
    void DoTurn();


  private:
    GameStateClass *gameState;

    //alpha=-inf beta=inf als startwert
    //Wenn mein Rating so hoch ist dass sicherer gewinn setze ich mich auf lastNode
    //Nur weiterrechnen wenn ich nicht lastNode bin
    //DoMove für alle Züge machen wenn ok dann neuen Node erzeugen welcher alle werte gesetzt hat durch konstruktor
    //Node( mich als eltern, getRating(), move, - my.negamax, my.depth-1, my.depth-1 == 0)
    //addChilde() machen auf mich mit diesem knoten
    //Danach für diesen Knoten wieder generatesubtree( der neue knoten)
    //nach dem zurückkommen unDoMove machen und nächster möglicher zug berechnen
    //Wenn alle Züge berechnet funktion beenden
    //
    //Rückgabewert ist gerade die bewertung des zuges also das maximum
    int32_t GenerateSubtree(NodeClass *currentNode, int endDepth);

  public:
    void CleanUpTreeAfterMove(int move);

    BotClass(GameStateClass *_gameState);

    ~BotClass();

    void PrintTree();

    void PrintPath();

    void PrintDebug();

    int maxDepth;

  private:
    int countNode;

    NodeClass *treeHead = nullptr;

    RatingClass rating;
};
#endif
