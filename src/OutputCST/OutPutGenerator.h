#ifndef ASSIGNMENT1_460_OUTPUTGENERATOR_H
#define ASSIGNMENT1_460_OUTPUTGENERATOR_H
#include "../CST/ConcreteSyntaxTree.h"
#include <fstream>
#include "../SymbolTable/SymbolTable.h"
class OutPutGenerator {
public:
    void PrintCST(NodePtr &);
    void PrintSymbolTables(SymTblPtr &root);

};


#endif //ASSIGNMENT1_460_OUTPUTGENERATOR_H