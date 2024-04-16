#ifndef NODE_H
#define NODE_H

#include "../Token/Token.h"
#include <memory> // Used for shared_ptr
#include <string>

// Forward declaration to resolve circular references
class Node;

// Alias for shared_ptr to Node for convenience
using NodePtr = std::shared_ptr<Node>; // shared_ptr used to help with automatic
                                       // memory cleanup

class Node {
  public:
    // Define an enum class for Key Semantic types
    enum class Type {
        DECLARATION,
        ASSIGNMENT,
        BEGIN_BLOCK,
        END_BLOCK,
        IF,
        ELSE,
        FOR,
        ForExpression1,
        ForExpression2,
        ForExpression3,
        WHILE,
        PRINTF,
        RETURN,
        OTHER,
    };
    // Function to convert Type to a string
    static std::string semanticTypeToString(Type type);
    void setSemanticType(Type newType); // set the type
    Type getSemanticType() const;       // get the type

    NodePtr Left();
    NodePtr Right();
    Token Value();

    // Constructor
    Node(const Token &val,
         Type type = Type::OTHER); // Set default type to OTHER

    // assign left child
    void addLeftChild(const NodePtr &nodePtr);

    // assign right sibling
    void addRightSibling(const NodePtr &nodePtr);

    Type nodeType; // Store the semantic type of the node
    Token value;   // Value of the node (could be a token or a non-terminal)
    NodePtr leftChild;
    NodePtr rightSibling;
};

#endif // NODE_H