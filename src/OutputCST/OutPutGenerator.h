#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H
#include "../CST/ConcreteSyntaxTree.h"
#include <fstream>
#include "../SymbolTable/SymbolTable.h"
class OutPutGenerator {
public:
    void PrintCST(NodePtr &);
    void PrintSymbolTables(SymTblPtr &root);

};


#endif // OUTPUTGENERATOR_H