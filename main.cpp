/*
 * Assignment: CS460 Interpreter
 * Authors: Evan Walters, Luis carmona, Ben Harris, Hanpei Zhang
 * Date: 2/8/24
 * Description:
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include "fileAsArray.h"
#include "Tokenizer.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    fileAsArray fileArray(argv[1]);
    fileArray.readFile();

    try {
        fileArray.File_w_no_comments();
    }
    catch (const std::exception& error) {
        cerr << "Exception caught: " << error.what() << endl;
        return 1; // Exit if there's an error
    }

    // Create a Tokenizer instance with the processed file content
    Tokenizer tokenizer(fileArray.getFileContent());

    // Tokenize the vector
    tokenizer.tokenizeVector();

    // Retrieve and print tokens (assuming you have methods to access and print token details)
    vector<Token> tokens = tokenizer.getTokens();
    for (const auto& token : tokens) {
        token.print();
    }

    return 0;
}