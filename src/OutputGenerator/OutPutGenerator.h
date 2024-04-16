#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H
#include "../CST/ConcreteSyntaxTree.h"
#include "../SymbolTable/SymbolTable.h"
#include <fstream>
class OutPutGenerator {
  public:
    void PrintCST(NodePtr &);
    void PrintAST(NodePtr &);
    void PrintAST(const NodePtr &root);

    void PrintSymbolTables(SymTblPtr &root);
};

#endif // OUTPUTGENERATOR_H