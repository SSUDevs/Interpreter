//
// Created by Luis carmona on 3/27/24.
//

#ifndef ASSIGNMENT1_460_SYMBOLTABLE_HPP
#define ASSIGNMENT1_460_SYMBOLTABLE_HPP

#include <iostream>
using namespace std;
class SymbolTable {
  public:
    enum class IDType{
        function,
        datatype,
        procedure
    };

    SymbolTable();
  private:
    string _idName,_dataType;
    IDType _idtype;
    bool _isArray;
    int _arraySize,_scope;

};

#endif // ASSIGNMENT1_460_SYMBOLTABLE_HPP
