//
// Created by Luis carmona on 3/19/24.
//

#ifndef ASSIGNMENT1_460_NODE_H
#define ASSIGNMENT1_460_NODE_H
#include "Token.h"

using namespace std;
class Node {
public:

Node(Token );
~Node();
Token &AToken();
Node &Right();
Node &left();

private:
    Token _token;
    Node *_left;
    Node *_right;
};


#endif //ASSIGNMENT1_460_NODE_H
