#include "ConcreteSyntaxTree.h"

NodePtr ConcreteSyntaxTree::Left() {
    return root->Left();
}
NodePtr ConcreteSyntaxTree::Right() {
    return root->Right();
}