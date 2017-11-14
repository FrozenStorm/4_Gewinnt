#include <iostream>
#include <fstream>
#include <time.h>
#include "BotClass.h"
#include "GameStateClass.h"
#include "FieldClass.h"

void BotClass::DoTurn() {
    if(gameState.round == 1){ //First Move always in the middle
        cout << "place_disc " << gameState.fieldColumns/2 << endl;
    }
    else if( gameState.round == 2){ // Second turn always beside the middle
        if(gameState.field->GetCellValue(gameState.fieldRows-1,gameState.fieldColumns/2) == -gameState.yourBotId){
            cout << "place_disc " << gameState.fieldColumns/2-1 << endl;
        }
        else{
            cout << "place_disc " << gameState.fieldColumns/2 << endl;
        }
    }
    else{
        if(treeHead != NULL) delete treeHead;
        treeHead = new NodeClass(NULL, rating.GetRating(gameState.yourBotId), -WINNIG_VALUE, WINNIG_VALUE, 0, gameState.yourBotId, maxDepth); // Generate the root of the tree
        GenerateSubtree(treeHead); // Starts the recursive callculation
        if(treeHead->moveTo != -1){ // Test if there was a move to do
            gameState.field->DoMove(treeHead->moveTo, treeHead->playerId);
            cout << "place_disc " << treeHead->moveTo << endl;
        }
        else{
            cout << "no_moves" << endl;
        }
    }
}

#ifdef USE_ALPHA_BETA
int32_t BotClass::GenerateSubtree(NodeClass *currentNode) {
    NodeClass *NextChildNode;           // Holds the next node while the callcuation
    int32_t maxValue = -WINNIG_VALUE-1; // Best value from a child to go. -1 because there should be one time value > maxValue if there is one move and the smallest value from rating ist -WINNIG_VALUE
    int32_t value;                      // Holds the return value from the recursive call of this function to compare with the maxValue and the barriers
    bool oneMoveDone = false;           // Indicates if there was at least one possible move from this situation
    if((currentNode->value == WINNIG_VALUE) || (currentNode->value == -WINNIG_VALUE)  || (currentNode->depth==0)) { // Check if it's a leaf node
        currentNode->isLast = true;
#ifdef DEBUG
cout << "this = " << currentNode;
cout << "  depth = " << currentNode->depth;
cout << "  countNode = " << countNode;
cout << "  alpha = " << currentNode->alpha;
cout << "  beta = " << currentNode->beta;
cout << "  value = " << currentNode->value;
cout << "  last" << endl;
#endif
        return currentNode->value;
    }
    for(int move=0; move<gameState.fieldColumns; move++){               // Go through all possible moves
        if(gameState.field->DoMove(move, currentNode->playerId)){
            oneMoveDone = true;
#ifdef DEBUG
cout << "this = " << currentNode;
cout << "  depth = " << currentNode->depth;
cout << "  alpha = " << currentNode->alpha;
cout << "  beta = " << currentNode->beta;
cout << "  value = " << currentNode->value;
cout << "  move = " << move << endl;
#endif
            NextChildNode = new NodeClass(currentNode, rating.GetRating(-currentNode->playerId), -currentNode->beta, -currentNode->alpha, move, -currentNode->playerId, currentNode->depth-1);
            currentNode->AddChild(NextChildNode);
            value = -GenerateSubtree(NextChildNode);    // recursive call for the new node
            gameState.field->UndoMove(move);
            if(value > currentNode->alpha) {
                currentNode->alpha = value;             // callcuate new alpha value
            }
            if(value > maxValue){                       // check if this move was the best until now
                maxValue = value;
                currentNode->moveTo = move;
                if(maxValue > currentNode->beta){       // check for a beta cut
                    currentNode->moveTo = -1;
                    break;  //Beta-cut
                }
                if(maxValue == WINNIG_VALUE){           // check for a winning cut
                    break;  //Winning-cut
                }
#ifdef DEBUG
cout << "this = " << currentNode;
cout << "  depth = " << currentNode->depth;
cout << "  alpha = " << currentNode->alpha;
cout << "  beta = " << currentNode->beta << endl;
#endif
            }
        }
    }

    if(oneMoveDone == true) currentNode->value = maxValue;  // set the value from this node to the value from the best option to go
    else currentNode->isLast = true;                        // If there was no possible move the field is full and it's a leaf node
    return currentNode->value;
}
#endif

#ifdef USE_DEEPSEARCH
int32_t BotClass::GenerateSubtree(NodeClass *currentNode){
    NodeClass *NextChildNode;
    int32_t maxValue = -WINNIG_VALUE;
    int32_t value;
    bool oneMoveDone = false;
    if((currentNode->value == WINNIG_VALUE) || (currentNode->value == -WINNIG_VALUE) || (currentNode->depth==0)) {
        currentNode->isLast = true;
#ifdef DEBUG
cout << "this = " << currentNode;
cout << "  depth = " << currentNode->depth;
cout << "  value = " << currentNode->value;
cout << "  last" << endl;
#endif
        return currentNode->value;
    }
    for(int move=0; move<gameState.fieldColumns; move++){
        if(gameState.field->DoMove(move, currentNode->playerId)){
            oneMoveDone = true;
#ifdef DEBUG
cout << "this = " << currentNode;
cout << "  depth = " << currentNode->depth;
cout << "  countNode = " << countNode;
cout << "  value = " << currentNode->value;
cout << "  move = " << move << endl;
#endif
            NextChildNode = new NodeClass(currentNode, rating.GetRating(-currentNode->playerId), -currentNode->beta, -maxValue, move, -currentNode->playerId, currentNode->depth-1);
            currentNode->AddChild(NextChildNode);
            value = -GenerateSubtree(NextChildNode);
            gameState.field->UndoMove(move);
            if(value > maxValue){
                maxValue = value;
            }
#ifdef DEBUG
cout << "this = " << currentNode;
cout << "  depth = " << currentNode->depth;
cout << "  MaxValue = " << maxValue << endl;
#endif
        }
    }

    if(oneMoveDone == true) currentNode->value = maxValue;
    else currentNode->isLast = true;
    return currentNode->value;
}
#endif

BotClass::BotClass(GameStateClass &_gameState, int _maxDepth) : gameState(_gameState), maxDepth(_maxDepth) , rating(_gameState){
}

BotClass::~BotClass(){
    delete treeHead;
}

void BotClass::PrintTree(){
    ofstream outfile("treeView.gv",ofstream::out);
    outfile << "digraph G {" << endl;
    outfile << "rankdir=LR;" << endl;
    outfile << "size=\"150\";" << endl;
    outfile << "node [shape=record];" << endl;
    if(treeHead != NULL) outfile << *treeHead;
    outfile << "}" << endl;
    outfile.close();
}

void BotClass::PrintDebug() {
    cout << "maxDepth = " << maxDepth << endl;
    cout << endl;
    if(treeHead != NULL) treeHead->PrintDebug();
}
