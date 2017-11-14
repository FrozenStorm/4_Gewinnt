#ifndef _RATINGCLASS_H
#define _RATINGCLASS_H

#include <iostream>
using namespace std;

class GameStateClass;

class RatingClass {
  public:

    RatingClass(GameStateClass *_gameState);

    int32_t GetRating(int playerId);

    int32_t HasWon(int playerId, int lastMove);

    void PrintDebug();

  private:
    GameStateClass *gameState;

};
#endif
