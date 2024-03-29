//
// Created by Luis carmona on 3/28/24.
//

#ifndef ASSIGNMENT1_460_SYMBOLTABLES_HPP
#define ASSIGNMENT1_460_SYMBOLTABLES_HPP
#include "SymbolTable.hpp"
#include"../CST/Node.h"
using namespace std;
class SymbolTables {
  public:
    void parse(NodePtr*);
  private:
    vector<SymbolTable> Tables;
};

#endif // ASSIGNMENT1_460_SYMBOLTABLES_HPP
