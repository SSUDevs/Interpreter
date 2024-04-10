/*
 * Assignment: CS460 Interpreter
 * Authors: Evan Walters, Luis carmona, Ben Harris, Hanpei Zhang
 * Date: 2/8/24
 * Description:
 *
 */

#include "./CST/Parser.h"
#include "./CommentRemoval/fileAsArray.h"
#include "./OutputCST/OutPutGenerator.h"
#include "./SymbolTable/SymbolTablesLinkedList.h"
#include "./Token/Tokenizer.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    fileAsArray fileArray(argv[1]);
    fileArray.readFile();

    try {
        fileArray.File_w_no_comments();
    } catch (const std::exception &error) {
        cerr << "Exception caught: " << error.what() << endl;
        return 1; // Exit if there's an error
    }

    // Create a Tokenizer instance with the processed file content
    Tokenizer tokenizer(fileArray.getFileContent());

    // Tokenize the vector
    tokenizer.tokenizeVector();

    // Retrieve and print tokens
    vector<Token> tokens = tokenizer.getTokens();
//        for (const auto &token : tokens) {
//            token.print();
//        }

//     Use the Parser to parse the tokenized input
    Parser parser(tokens);
    auto cstRoot = parser.parse(); // Root of the Concrete Syntax Tree

    OutPutGenerator output;

    // Method to print or inspect CST
    // output.PrintCST(cstRoot);

    // Generate symbol tables from the CST
    SymbolTablesLinkedList tables(cstRoot);

    auto symTableRoot =
        tables.parse(); // Parse the CST to generate symbol tables

    // Print the Symbol Tables
    //output.PrintSymbolTables(symTableRoot);

    return 0;
}