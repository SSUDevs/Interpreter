#ifndef NODE_H
#define NODE_H

#include <memory> // Used for shared_ptr
#include <string>
#include "../Token/Token.h"

// Forward declaration to resolve circular references
class Node;

// Alias for shared_ptr to Node for convenience
using NodePtr = std::shared_ptr<Node>; // shared_ptr used to help with automatic memory cleanup 

class Node {
public:
    Token value;             // Value of the node (could be a token or a non-terminal)
    NodePtr leftChild;             
    NodePtr rightSibling;

    NodePtr Left();
    NodePtr Right();
    Token Value();

    // Constructor
    Node(const Token& val);

    // assign left child
    void addLeftChild(const NodePtr& nodePtr);

    // assign right sibling
    void addRightSibling(const NodePtr& nodePtr);


    // Used to add a connection to node
    //void addConnection(const NodePtr& connection);
};


#endif // NODE_H
