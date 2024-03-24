//
// Created by Luis carmona on 3/19/24.
//

#include "ConcreteSyntaxTree.h"

NodePtr ConcreteSyntaxTree::Left() {
    return root->Left();
}
NodePtr ConcreteSyntaxTree::Right() {
    return root->Right();
}
