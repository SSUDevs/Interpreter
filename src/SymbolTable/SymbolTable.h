//
// Created by Luis carmona on 3/27/24.
//

#ifndef ASSIGNMENT1_460_SYMBOLTABLE_H
#define ASSIGNMENT1_460_SYMBOLTABLE_H

#include <iostream>
#include <memory> // Used for shared_ptr


// Forward declaration to resolve circular references
class SymbolTable;

// Alias for shared_ptr to Node for convenience
using SymTblPtr = std::shared_ptr<SymbolTable>; // shared_ptr used to help with automatic memory cleanup

using namespace std;
class SymbolTable {
  public:
    enum class IDType{
        function,
        datatype,
        procedure
    };

    SymbolTable();

    string _idName,_dataType;
    IDType _idtype;
    bool _isArray;
    int _arraySize,_scope;
    SymTblPtr nextTable = nullptr;

};

#endif // ASSIGNMENT1_460_SYMBOLTABLE_H
