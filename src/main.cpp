/*
 * Assignment: CS460 Interpreter
 * Authors: Evan Walters, Luis carmona, Ben Harris, Hanpei Zhang
 * Date: 2/8/24
 * Description:
 *
 */

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
    //output.PrintCST(cstRoot);

    // Generate symbol tables from the CST
    // SymbolTablesLinkedList tables(cstRoot);

    // auto symTableRoot =
    //     tables.parse(); // Parse the CST to generate symbol tables

    // // Print the Symbol Tables
    // output.PrintSymbolTables(symTableRoot);

    // Now, generate the AST from the CST
    ASTParser astParser(cstRoot);
    auto astRoot = astParser.parse();

    // Optionally print the AST using a similar method
    output.PrintAST(astRoot);



//    // VERY HARD CODED INFIX to POSTFIX testing
//        using NodePtr = std::shared_ptr<Node>;
//        vector<Token> temp;
//
//        temp.push_back(Token(Token::Type::Identifier, "0", 0));
//        temp.push_back(Token(Token::Type::LBracket, "0", 0));
//        temp.push_back(Token(Token::Type::Integer, "0", 0));
//        temp.push_back(Token(Token::Type::Plus, "0", 0));
//        temp.push_back(Token(Token::Type::Identifier, "0", 0));
//        temp.push_back(Token(Token::Type::RBracket, "0", 0));
//        temp.push_back(Token(Token::Type::AssignmentOperator, "0", 0));
//        temp.push_back(Token(Token::Type::LParen, "0", 0));
//        temp.push_back(Token(Token::Type::Identifier, "0", 0));
//        temp.push_back(Token(Token::Type::Gt, "0", 0));
//        temp.push_back(Token(Token::Type::Integer, "0", 0));
//        temp.push_back(Token(Token::Type::RParen, "0", 0));
//        temp.push_back(Token(Token::Type::BooleanAnd, "0", 0));
//        temp.push_back(Token(Token::Type::BooleanNot, "0", 0));
//        temp.push_back(Token(Token::Type::LParen, "0", 0));
//        temp.push_back(Token(Token::Type::Identifier, "0", 0));
//        temp.push_back(Token(Token::Type::Lt, "0", 0));
//        temp.push_back(Token(Token::Type::Integer, "0", 0));
//        temp.push_back(Token(Token::Type::RParen, "0", 0));
//
//        vector<NodePtr> testIn;
//
//        for (int i = 0; i < temp.size(); ++i) {
//            testIn.push_back(make_shared<Node>(temp[i]));
//        }
//
//        auto testOut = inToPostFix(testIn);
//
//        for (int i = 0; i < testOut.size(); ++i) {
//            cout << Token::typeToString(testOut[i]->value.type()) << endl;
//        }

    return 0;
}