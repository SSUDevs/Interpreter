#ifndef CONCRETESYNTAXTREE_H
#define CONCRETESYNTAXTREE_H
#include"../Token/Token.h"
#include "../Node/Node.h" 
#include <vector>
using namespace std;
class ConcreteSyntaxTree {
public:
    NodePtr Left();
    NodePtr Right();

private:
    Node *root;
};


#endif // CONCRETESYNTAXTREE_H