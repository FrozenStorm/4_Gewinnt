#ifndef _NODECLASS_H
#define _NODECLASS_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class NodeClass {
  public:
    NodeClass();

    NodeClass(int32_t _id, NodeClass *_parent, int32_t _value, int32_t _alpha, int32_t _beta, int _moveFrom, int _playerId, int _depth, int maxChildern);

    ~NodeClass();

    void deleteChildern(void);

    inline void AddChild(NodeClass *child){childern.push_back(child);}

    void decreaseDepthByOneForSubTree(void);

    void PrintDebug();

    int32_t id;

    NodeClass *parent = nullptr;

    int32_t value;

    int32_t alpha;

    int32_t beta;

    //Move to get to this point from parent node
    int moveFrom;

    //Best move to Do from here
    int moveTo;

    int playerId;

    int depth;

    bool isLast; //Is true when the node is a final game situation ( no more move possible or one player has won) if it's set ones this node will never be recalculated in the tree

    vector<NodeClass*> childern;

    friend ostream& operator <<(ostream &out, NodeClass &Source);
};


#endif
