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

    SymbolTable(std::string _procOrFuncName = "", std::string idName = "", std::string dataType = "",
                IDType idtype = IDType::datatype, int scope = 0,
                bool isArray = false, int arraySize = 0)
        : _idName(idName), _dataType(dataType), _idtype(idtype), _scope(scope),
          _isArray(isArray), _arraySize(arraySize) {}

    std::string procOrFuncName(){return _procOrFuncName;}
    std::string Name(){return _idName;}
    std::string dataType(){return _dataType;}
    std::string isArray(){if(_isArray){return "yes";}else{return "no";}}
    int arraySize(){return _arraySize;}
    int scope(){return _scope;}
    std::string idType(){
        if(_idtype==IDType::function){
            return "function";
        }
        else if(_idtype==IDType::datatype){
            return "dataType";
        }
        else if(_idtype==IDType::procedure){
            return "procedure";
        }
        else {
            cerr << "ID Type not identifiable." << endl;
            exit(100);
        }
    }

    string _idName, _dataType, _procOrFuncName;
    IDType _idtype;
    bool _isArray;
    int _arraySize, _scope;
    SymTblPtr nextTable = nullptr;

};

#endif // ASSIGNMENT1_460_SYMBOLTABLE_H
