/*
 * Assignment: CS460 Interpreter
 * Authors: Evan Walters, Luis carmona, Ben Harris, Hanpei Zhang
 * Date: 2/8/24
 * Description:
 *
 */

#include "./Interpreter/Interpreter.h"
#include "./AST/ASTParser.h"
#include "./CST/Parser.h"
#include "./CommentRemoval/fileAsArray.h"
#include "./OutputGenerator/OutPutGenerator.h"
#include "./SymbolTable/SymbolTablesLinkedList.h"
#include "./Token/Tokenizer.h"

#include "./Node/Node.h"
#include "./Token/Token.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <filename> <option>" << endl;
        return 1;
    }

    string filename = argv[1];
    string option = argv[2];

    fileAsArray fileArray(filename);
    fileArray.readFile();

    try
    {
        fileArray.File_w_no_comments();
    }
    catch (const std::exception &error)
    {
        cerr << "Exception caught: " << error.what() << endl;
        return 1;
    }

    Tokenizer tokenizer(fileArray.getFileContent());
    tokenizer.tokenizeVector();
    vector<Token> tokens = tokenizer.getTokens();

    if (option == "tokens")
    {
        for (const auto &token : tokens)
        {
            token.print();
        }
        return 0;
    }

    Parser parser(tokens);
    auto cstRoot = parser.parse();

    if (option == "cst")
    {
        OutPutGenerator CSToutput;
        CSToutput.PrintCST(cstRoot);
        return 0;
    }

    SymbolTablesLinkedList tables(cstRoot);
    auto symTableRoot = tables.parse();

    ASTParser astParser(cstRoot);
    auto astRoot = astParser.parse();

    if (option == "symbolTable")
    {

        OutPutGenerator STOutput;
        STOutput.PrintSymbolTables(symTableRoot);
        return 0;
    }

    if (option == "ast")
    {
        OutPutGenerator ASOutput;
        ASOutput.PrintAST(astRoot);
        return 0;
    }

    if (option == "run")
    {
        Interpreter interpret(astRoot, symTableRoot);
    }

    return 0;
}
