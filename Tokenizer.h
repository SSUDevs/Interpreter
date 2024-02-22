#ifndef INTERPRETER_TOKENIZER_H
#define INTERPRETER_TOKENIZER_H
#include "Token.h"

class Tokenizer
{
public:
    // Pass vector created from fileAsArray that has removed comments
    Tokenizer(std::vector<char>); 

    Token getToken(); // Gets the next token from the vector

private:
    std::vector<char> _file; 
    bool charOfInterest(char c); // Defines all tokens in language
    size_t currentPos = 0; // Tracks the current position in the vector as its being tokenized
    int _errorLineNumber; // Keeps track of line number during parsing when error found
};

#endif // INTERPRETER_TOKENIZER_H
