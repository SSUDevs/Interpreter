#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <memory> // Used for shared_ptr
#include <vector>

using std::make_shared;
using std::shared_ptr;
using std::string;

using namespace std;

class SymbolTable;

// Alias for shared_ptr to SymbolTable for convenience
using SymTblPtr = std::shared_ptr<SymbolTable>;

class SymbolTable {
  public:
    enum class IDType { function, datatype, procedure, parameterList };

    // Ensure constructor parameters match expected usage
    SymbolTable(string idName = "", string dataType = "",
                IDType idtype = IDType::datatype, int scope = 0,
                bool isArray = false, int arraySize = 0,
                string procOrFuncName = "")
        : _idName(idName), _dataType(dataType), _idtype(idtype), _scope(scope),
          _isArray(isArray), _arraySize(arraySize),
          _procOrFuncName(procOrFuncName) {}

    void SetNextTable(const SymTblPtr &next);
    void setDeclared(const bool dec) {_isDeclared = dec;}
    void setValueSize(const int size) {_value.resize(size);}
    void setValue(int newVal , int index = 0) {
        if (_dataType == "bool") {
            if (newVal != 0) {
                _value.at(index) = 1;
            }
            else {
                _value.at(index) = 0;
            }
        }
            _value.at(index) = newVal;
    }

    string GetName() const { return _idName; }
    string GetDataType() const { return _dataType; }
    string GetIsArray() const { return _isArray ? "yes" : "no"; }
    bool isArray() const { return _isArray;}
    vector<int> &GetValue() {return _value;}
    int GetArraySize() const { return _arraySize; }
    int GetScope() const { return _scope; }
    SymTblPtr GetNextTable() const { return nextTable; }
    bool GetIsDeclared() const {return _isDeclared; }
    std::string procOrFuncName() { return _procOrFuncName; }



    string GetStringIdType() const {
        switch (_idtype) {
        case IDType::function:
            return "function";
        case IDType::datatype:
            return "datatype";
        case IDType::procedure:
            return "procedure";
        case IDType::parameterList:
            return "parameterList";
        default:
            return "Unknown";
        }
    }
    IDType GetIdType() const {
        switch (_idtype) {
        case IDType::function:
            return IDType::function;
        case IDType::datatype:
            return IDType::datatype;
        case IDType::procedure:
            return IDType::procedure;
        case IDType::parameterList:
            return IDType::parameterList;
        default:
            return IDType::datatype;
        }
    }

  private:
    string _idName, _dataType, _procOrFuncName;
    IDType _idtype;
    bool _isDeclared = false;
    bool _isArray;
    int _arraySize, _scope;

    vector<int> _value;

    SymTblPtr nextTable = nullptr;
};

#endif // SYMBOLTABLE_H
