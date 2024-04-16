#ifndef AST_H
#define AST_H
#include "../Node/Node.h"
#include <vector>

using namespace std;

class AST {
  public:
    NodePtr Left();
    NodePtr Right();

  private:
    Node *root;
};

#endif // AST_H
