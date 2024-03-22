#ifndef NODE_H
#define NODE_H

#include <memory> // Used for shared_ptr
#include <string>

// Forward declaration to resolve circular references
class Node;

// Alias for shared_ptr to Node for convenience
using NodePtr = std::shared_ptr<Node>; // shared_ptr used to help with automatic memory cleanup 

class Node {
public:
    std::string value;             // Value of the node (could be a token or a non-terminal)
    NodePtr leftChild;             
    NodePtr rightChild;          


    // Constructor
    Node(const std::string& val);

    // Used to add a child to node
    void addChild(const NodePtr& child);
};


#endif // NODE_H
