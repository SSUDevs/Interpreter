#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"
#include <cctype> // For isspace, isalpha, etc..
#include <vector>

class Tokenizer {
  public:
    enum State {
        START,
        IDENTIFIER,
        INTEGER,
        DQ_STRING,
        SQ_STRING,
    };

    explicit Tokenizer(const std::vector<char> &file); // Pass by const ref

    bool isOperator(Token t);
    bool isOperator(char t);

    void tokenizeVector();
    std::vector<Token> getTokens() const;

  private:
    std::vector<char> _file;
    std::vector<Token> _tokens;
    size_t _currentPos = 0; // index as we tokenize
    size_t _size;           // To store the size of vector passed in
    size_t _lineNum = 1;    // for error output
    State _currentState = START;

    Token getToken();
};

#endif // TOKENIZER_H