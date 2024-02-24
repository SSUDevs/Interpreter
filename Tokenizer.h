// Tokenizer.h corrections
#ifndef INTERPRETER_TOKENIZER_H
#define INTERPRETER_TOKENIZER_H

#include "Token.h"
#include <cctype> // For isspace, isalpha, etc..
#include <vector>

class Tokenizer {
  public:
    enum State {
        START,
        IDENTIFIER,
        NUMBER
        // STRING not yet implemented
    };

    explicit Tokenizer(const std::vector<char> &file); // Pass by const ref

    void tokenizeVector();
    std::vector<Token> getTokens() const;

  private:
    std::vector<char> _file;
    std::vector<Token> _tokens;
    size_t _currentPos = 0; // index as we tokenize
    size_t _size;           // To store the size of vector passed in
    State _currentState = START;

    Token getToken();
};

#endif // INTERPRETER_TOKENIZER_H