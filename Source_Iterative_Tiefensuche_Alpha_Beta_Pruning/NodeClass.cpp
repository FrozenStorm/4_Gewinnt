#include <iostream>
#include "NodeClass.h"

NodeClass::NodeClass(){

}

NodeClass::NodeClass(int32_t _id, NodeClass *_parent, int32_t _value, int32_t _alpha, int32_t _beta, int _moveFrom, int _playerId, int _depth, int maxChildern) : id(_id) , parent(_parent) , value(_value) , alpha(_alpha) , beta(_beta) , moveFrom(_moveFrom) , moveTo(-1), playerId(_playerId) , depth(_depth) , isLast(false), childern(maxChildern, NULL){
}

NodeClass::~NodeClass(){
    /* No more needed because of safeing Tree between rounds and only delete selective Nodes in cleanUpTreeAfterMove()
    for(childernIterator = childern.begin(); childernIterator != childern.end(); childernIterator++){
        delete *childernIterator;
    }*/
}

void NodeClass::deleteChildern(){
    for(unsigned int i=0; i < childern.size(); i++){
        if(childern[i] != NULL){
            childern[i]->deleteChildern();
            delete childern[i];
            childern[i] = NULL;
        }
    }
}

void NodeClass::decreaseDepthByOneForSubTree(){
    depth--;
    for(unsigned int i=0; i < childern.size(); i++){
        if(childern[i] != NULL) childern[i]->decreaseDepthByOneForSubTree();
    }
}

void NodeClass::PrintDebug() {
    cout << "this = " << this << endl;
    cout << "id = " << id << endl;
    cout << "parent = " << parent << endl;
    cout << "value = " << value << endl;
    cout << "alpha = " << alpha << endl;
    cout << "beta = " << beta << endl;
    cout << "moveFrom = " << moveFrom << endl;
    cout << "moveTo = " << moveTo << endl;
    cout << "playerId = " << playerId << endl;
    cout << "depth = " << depth << endl;
    cout << "isLast = " << isLast << endl;
    cout << "childern count = " << childern.size() << endl;
    cout << endl;
    for(unsigned int i=0; i < childern.size(); i++){
        if(childern[i] != NULL) childern[i]->PrintDebug();
    }
}

// This function only works correct on the first call because of static use but this is ok because the hole program will be called only one time
ostream& operator <<(ostream &out, NodeClass &Source){
    static int32_t FromNodeId = Source.id;
    static int headPlayerId = Source.playerId;

    // Color it different for each player
    if(headPlayerId == Source.playerId ){
        out << Source.id << " [color=green label=\"" << Source.alpha << "|" << Source.value << "|" << Source.beta << "\" ];" << endl;
    }
    else{
        out << Source.id << " [color=black label=\"" << Source.alpha << "|" << Source.value << "|" << Source.beta << "\" ];" << endl;
    }

    // Go through all childern and make the arrows
    if(Source.isLast == false){
        for(unsigned int i=0; i < Source.childern.size(); i++){
            if(Source.childern[i] != NULL){
                if(Source.id == FromNodeId && Source.moveTo == Source.childern[i]->moveFrom) {
                    FromNodeId = Source.childern[i]->id;
                    out << Source.id << " -> " << Source.childern[i]->id << " [color=red, label=\"" << Source.childern[i]->moveFrom << "\" ];" << endl;
                }
                else{
                    out << Source.id << " -> " << Source.childern[i]->id << " [label=\"" << Source.childern[i]->moveFrom << "\" ];" << endl;
                }
            }
        }
    }
    // Recursive call to print all childern
    for(unsigned int i=0; i < Source.childern.size(); i++){
        if(Source.childern[i] != NULL) out << *Source.childern[i];
    }
    return out;
}
