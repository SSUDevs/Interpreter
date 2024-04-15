#ifndef AST_HPP
#define AST_HPP
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

#endif // AST_HPP
