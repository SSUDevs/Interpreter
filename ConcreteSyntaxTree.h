//
// Created by Luis carmona on 3/19/24.
//

#ifndef ASSIGNMENT1_460_CONCRETESYNTAXTREE_H
#define ASSIGNMENT1_460_CONCRETESYNTAXTREE_H
#include"Token.h"
#include "Node.h"
using namespace std;
class ConcreteSyntaxTree {
public:
    ConcreteSyntaxTree();
    ~ConcreteSyntaxTree();
    void CreateTree(vector<Token>);
    void insert(Token);

private:
    Node *root;

};


#endif //ASSIGNMENT1_460_CONCRETESYNTAXTREE_H
