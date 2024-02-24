// Tokenizer.h corrections
#ifndef INTERPRETER_TOKENIZER_H
#define INTERPRETER_TOKENIZER_H

#include "Token.h"
#include <vector>
#include <cctype> // For isspace, isalpha, etc..

class Tokenizer {
    public:
        enum State {
            START, IDENTIFIER, NUMBER, INTEGER,
            DQ_STRING, DQ_END, SQ_STRING, SQ_END
        };

        explicit Tokenizer(const std::vector<char>& file); // Pass by const ref

        bool isOperator(Token t);
        void tokenizeVector();
        std::vector<Token> getTokens() const;

    private:
        std::vector<char> _file;
        std::vector<Token> _tokens;
        size_t _currentPos = 0; // index as we tokenize
        size_t _size; // To store the size of vector passed in
        size_t _lineNum = 1;  // for error output
        State _currentState = START;

        Token getToken();
};

#endif // INTERPRETER_TOKENIZER_H