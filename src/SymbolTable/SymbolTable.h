#ifndef ASSIGNMENT1_460_SYMBOLTABLE_H
#define ASSIGNMENT1_460_SYMBOLTABLE_H

#include <iostream>
#include <memory> // Used for shared_ptr

// Forward declaration to resolve circular references
class SymbolTable;

// Alias for shared_ptr to Node for convenience
using SymTblPtr = std::shared_ptr<SymbolTable>; // shared_ptr used to help with
                                                // automatic memory cleanup

using namespace std;
class SymbolTable {
  public:
    enum class IDType { function, datatype, procedure, parameterList };

    SymbolTable(std::string idName = "", std::string dataType = "",
                IDType idtype = IDType::datatype, int scope = 0,
                bool isArray = false, int arraySize = 0)
        : _idName(idName), _dataType(dataType), _idtype(idtype), _scope(scope),
          _isArray(isArray), _arraySize(arraySize) {}

    string _idName, _dataType;
    IDType _idtype;
    bool _isArray;
    int _arraySize, _scope;
    SymTblPtr nextTable = nullptr;

};

#endif // ASSIGNMENT1_460_SYMBOLTABLE_H
