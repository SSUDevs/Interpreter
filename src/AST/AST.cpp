#include "AST.h"

NodePtr AST::Left() {
    return root->Left();
}
NodePtr AST::Right() {
    return root->Right();
}