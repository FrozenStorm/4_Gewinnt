#include <iostream>
#include "NodeClass.h"

int32_t NodeClass::countNode = 0;

NodeClass::NodeClass(NodeClass *_parent, int32_t _value, int32_t _alpha, int32_t _beta, int _moveFrom, int _playerId, int _depth) : id(countNode) , parent(_parent) , value(_value) , alpha(_alpha) , beta(_beta) , moveFrom(_moveFrom) , moveTo(-1), playerId(_playerId) , depth(_depth) , isLast(false){
    countNode++;
}

NodeClass::~NodeClass(){
    countNode--;
    for(childernIterator = childern.begin(); childernIterator != childern.end(); childernIterator++){
        delete *childernIterator;
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
    for(childernIterator = childern.begin(); childernIterator != childern.end(); childernIterator++){
        (**childernIterator).PrintDebug();
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

    // To through all childern and make the arrows
    for(Source.childernIterator = Source.childern.begin(); Source.childernIterator != Source.childern.end(); Source.childernIterator++){
        if(Source.id == FromNodeId && Source.moveTo == (**Source.childernIterator).moveFrom) {
            FromNodeId = (**Source.childernIterator).id;
            out << Source.id << " -> " << (**Source.childernIterator).id << " [color=red, label=\"" << (**Source.childernIterator).moveFrom << "\" ];" << endl;
        }
        else{
            out << Source.id << " -> " << (**Source.childernIterator).id << " [label=\"" << (**Source.childernIterator).moveFrom << "\" ];" << endl;
        }
    }

    // Recursive call to print all childern
    for(Source.childernIterator = Source.childern.begin(); Source.childernIterator != Source.childern.end(); Source.childernIterator++){
        out << **Source.childernIterator;
    }
    return out;
}
