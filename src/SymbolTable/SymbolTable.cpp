#include "SymbolTable.h"


void SymbolTable::SetNextTable(const SymTblPtr &next) {
    this->nextTable = next;
}
