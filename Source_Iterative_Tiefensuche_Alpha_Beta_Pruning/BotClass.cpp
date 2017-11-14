#include <iostream>
#include <fstream>
#include <time.h>
#include "BotClass.h"
#include "GameStateClass.h"
#include "FieldClass.h"

void BotClass::DoTurn() {
    int move = -1;
    if(gameState->round == 1){
        move = gameState->fieldColumns/2;
    }
    else if(gameState->round == 2){
        if(gameState->field->GetCellValue(gameState->fieldRows-1,gameState->fieldColumns/2) == -gameState->yourBotId){
            move = gameState->fieldColumns/2-1;
        }
        else{
            move = gameState->fieldColumns/2;
        }
    }
    else{
        //while(maxDepth < 12){
        while((((clock() - gameState->startTime) * 1000.0 / CLOCKS_PER_SEC) < gameState->timePerMove * 3.0) && (((clock() - gameState->startTime) * 1000.0 / CLOCKS_PER_SEC) < gameState->timebank * 0.7) && (maxDepth < 44)){ //ToDo stimmt dies für die berechnung der restzeit ist dies die restzeit welche das spiel mir gibt
            if(treeHead == NULL){
                treeHead = new NodeClass(countNode, NULL, rating.GetRating(gameState->yourBotId), -WINNIG_VALUE, WINNIG_VALUE, -1, gameState->yourBotId, 0, gameState->fieldColumns);
            }
            GenerateSubtree(treeHead, maxDepth);
#ifdef DEBUG
    cout << "maxDepth = " << maxDepth << "   countNode = " << countNode <<"    Timeleft after this iteration = " << gameState->timePerMove-((clock() - gameState->startTime) * 1000 / CLOCKS_PER_SEC) << "ms" << endl;
#endif
            maxDepth++; // TODO ? +2 weil stabieler
            if(treeHead != NULL){
//#ifdef DEBUG
    PrintPath();
    cout << "maxDepth = " << maxDepth << "   time used = " << (clock() - gameState->startTime) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
//#endif
                if(treeHead->value == WINNIG_VALUE || treeHead->value == -WINNIG_VALUE) break; //Stop if a winning situation was calculated
            }
        }
        if(treeHead != NULL){
            move = treeHead->moveTo;
        }
    }

    if(move != -1){
        cin.clear();
        fflush(stdin);
        cout << "place_disc " << move << endl;
    }
    else{
         cout << "no_moves" << endl;
    }
}

int32_t BotClass::GenerateSubtree(NodeClass *currentNode, int endDepth) {
    int32_t maxValue = -WINNIG_VALUE-1; // -1 because there should be one time value > maxValue if there is one move and the smallest value from rating ist -WINNIG_VALUE
    int32_t value = 0;
    int move = 0;
    int BestMoveFromBefore = 0;
    bool oneMoveDone = false;

#ifdef DEBUG
cout << "  depth = " << currentNode->depth;
cout << "  id = " << currentNode->id;
cout << "  move = " << currentNode->moveFrom;
cout << "  alpha = " << currentNode->alpha;
cout << "  beta = " << currentNode->beta;
cout << "  value = " << currentNode->value;
cout << endl;
#endif

    if(currentNode->isLast == true){
#ifdef DEBUG
cout << "last" << endl;
#endif
        return currentNode->value;
    }

    if((currentNode->value == WINNIG_VALUE) || (currentNode->value == -WINNIG_VALUE)) {
        currentNode->moveTo = -1;
        currentNode->isLast = true;
#ifdef DEBUG
cout << "winnig node" << endl;
#endif
        return currentNode->value;
    }

    if(currentNode->depth==endDepth){
        currentNode->value = rating.GetRating(currentNode->playerId); // Calculate exact rating for the last nodes
        currentNode->moveTo = -1;
#ifdef DEBUG
cout << "max depth reached   value = " << currentNode->value << endl;
#endif
        return currentNode->value;
    }

    if(currentNode->moveTo != -1) BestMoveFromBefore = currentNode->moveTo;
    else BestMoveFromBefore = currentNode->childern.size() / 2; //Test the middle one first because they are the best moves normally


    for(unsigned int i=0; i<currentNode->childern.size(); i++){
        move = (i + BestMoveFromBefore) % currentNode->childern.size(); // Go throw all possible moves starting by the best turn from the iteration before
        if(gameState->field->DoMove(move, currentNode->playerId)){
            oneMoveDone = true;

            if(currentNode->childern[move] == NULL){
                countNode++;
                currentNode->childern[move] = new NodeClass(countNode, currentNode, -rating.HasWon(currentNode->playerId,move), -currentNode->beta, -currentNode->alpha, move, -currentNode->playerId, currentNode->depth+1, gameState->fieldColumns);
            }
            else{
                if(currentNode->childern[move]->isLast == false){
                    currentNode->childern[move]->alpha = -currentNode->beta;
                    currentNode->childern[move]->beta = -currentNode->alpha;
                    //currentNode->childern[move]->value = -rating.HasWon(currentNode->playerId,move); //Auskommentiert weil nicht nötig
                }
            }

            value = -GenerateSubtree(currentNode->childern[move], endDepth);
            gameState->field->UndoMove(move);
            if(value > currentNode->alpha) {
                currentNode->alpha = value;
            }
            if(value > maxValue){
                maxValue = value;
                currentNode->moveTo = move;
                if(maxValue > currentNode->beta){
                    //currentNode->moveTo = -1;
#ifdef DEBUG
cout << "Beta-cut" << endl;
#endif
                    break;  //Beta-cut
                }
                if(maxValue == WINNIG_VALUE){
#ifdef DEBUG
cout << "Winning-cut" << endl;
#endif
                    break;  //Winning-cut
                }
            }
        }
        if((((clock() - gameState->startTime) * 1000.0 / CLOCKS_PER_SEC) >= gameState->timebank * 0.7) || (((clock() - gameState->startTime) * 1000.0 / CLOCKS_PER_SEC) >= gameState->timePerMove * 3.0)){
            //if(currentNode->moveTo == -1) currentNode->value = rating.GetRating(currentNode->playerId); //Only refresh value if it has not be callculated befor
            //currentNode->moveTo = -1;
#ifdef DEBUG
cout << "time is up" << endl;
#endif
            //return currentNode->value;
            break; //time is up
        }
    }

    if(oneMoveDone == true) currentNode->value = maxValue;
    else currentNode->isLast = true;
    return currentNode->value;
}

// ToDo optimieren zu langsam
void BotClass::CleanUpTreeAfterMove(int move){
    int predictedMove;
    if(treeHead != NULL && move >= 0 && move < gameState->fieldColumns){
        predictedMove = treeHead->moveTo;
        NodeClass *TreeHeadNew = treeHead->childern[move];
        for(unsigned int i=0; i < treeHead->childern.size(); i++){
            if((int)i != move) {
                if(treeHead->childern[i] != NULL){
                    treeHead->childern[i]->deleteChildern();
                    delete treeHead->childern[i];
                    treeHead->childern[i] = NULL;
                }
            }
        }

        delete treeHead;
        treeHead = NULL;
        treeHead = TreeHeadNew;
        if(treeHead != NULL)
        {
            treeHead->moveFrom = -1;
            treeHead->parent = NULL;
            //treeHead->value = rating.GetRating(gameState->yourBotId);
            treeHead->alpha = -WINNIG_VALUE;
            treeHead->beta = WINNIG_VALUE;
            treeHead->decreaseDepthByOneForSubTree();
            if(maxDepth > 1) maxDepth--;
            if(predictedMove != move) maxDepth = 1; //If oponet did a not predicted move recalculate tree from top because it could be very short
        }
        else{
            countNode = 0;
            maxDepth = 1;
#ifdef DEBUG
cout << "Error no child calculated befor";
#endif
        }
    }
    else{
        delete treeHead;
        treeHead = NULL;
        countNode = 0;
        maxDepth = 1;
#ifdef DEBUG
cout << "Error iregulare move or tree";
#endif
    }
}

BotClass::BotClass(GameStateClass *_gameState) : gameState(_gameState) , maxDepth(1) , countNode(0) , rating(_gameState){
}

BotClass::~BotClass(){
    delete treeHead;
    treeHead = NULL;
}

void BotClass::PrintTree()
{
    ofstream outfile("treeView.gv",ofstream::out);
    outfile << "digraph G {" << endl;
    outfile << "rankdir=LR;" << endl;
    outfile << "size=\"150\";" << endl;
    outfile << "node [shape=record];" << endl;
    if(treeHead != NULL) outfile << *treeHead;
    outfile << "}" << endl;
    outfile.close();
}

void BotClass::PrintPath(){
    NodeClass *myNode = treeHead;
    cout << "Selected Path: ";
    while(myNode != NULL && myNode->moveTo != -1){
    if(myNode->playerId > 0) cout << myNode->moveTo << ",";
    else cout << "-" << myNode->moveTo << ",";
    if(myNode->moveTo != -1) myNode = myNode->childern[myNode->moveTo];
}
cout << endl;
}

void BotClass::PrintDebug() {
    cout << "maxDepth = " << maxDepth << endl;
    cout << "coutNode = " << countNode << endl;
     cout << endl;
    //if(treeHead != NULL) treeHead->PrintDebug();
}
