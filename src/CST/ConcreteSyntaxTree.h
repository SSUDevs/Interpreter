#ifndef CONCRETESYNTAXTREE_H
#define CONCRETESYNTAXTREE_H
#include"../Token/Token.h"
#include "Node.h"
#include <vector>
using namespace std;
class ConcreteSyntaxTree {
public:
    ConcreteSyntaxTree();
    ~ConcreteSyntaxTree();
    void CreateTree(vector<Token>);
    void insert(Token);

    NodePtr Left();
    NodePtr Right();

private:
    Node *root;

};


#endif // CONCRETESYNTAXTREE_H