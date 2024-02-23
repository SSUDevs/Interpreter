#include "Tokenizer.h"
#include <iostream>
#include <sstream>

Tokenizer::Tokenizer(const std::vector<char>& file) : _file(file), _size(file.size()) 
{
}


void Tokenizer::tokenizeVector() {
    _currentPos = 0;
    _currentState = START; 
    while (_currentPos < _size) {
        Token token = getToken(); // Gonna get the next token
        if (token.type() != Token::Type::Unknown) { // Skiping unknown tokens for now
            _tokens.push_back(token);
        }
    }
}

Token Tokenizer::getToken() {
    std::string tokenValue;
    Token::Type tokenType = Token::Type::Unknown;
    bool tokenFound = false;

    while (_currentPos < _size && !tokenFound) {
        char currentChar = _file[_currentPos];
        switch (_currentState) {
            case START:
                if (std::isspace(currentChar)) {
                    // Ignore whitespace
                } else if (std::isalpha(currentChar)) {
                    tokenType = Token::Type::Identifier;
                    _currentState = IDENTIFIER;
                    tokenValue += currentChar;
                } else if (std::isdigit(currentChar)) {
                    tokenType = Token::Type::WholeNumber; // I think needs to be updated cause a sign could come before (so for ints)
                    _currentState = NUMBER;
                    tokenValue += currentChar;
                } else {
                    // Handling for single char tokens (ops, punctuation, ect...)
                    switch (currentChar) {
                        case '(':
                            tokenType = Token::Type::LParen;
                            tokenValue = currentChar;
                            tokenFound = true;
                            break;
                        case ')':
                            tokenType = Token::Type::RParen;
                            tokenValue = currentChar;
                            tokenFound = true;
                            break;
                        // Add cases for other single-character tokens here
                        default:
                            tokenType = Token::Type::Unknown;
                            tokenValue = currentChar;
                            tokenFound = true;
                            break;
                    }
                }
                break;
            case IDENTIFIER:
                if (std::isalnum(currentChar) || currentChar == '_') {
                    tokenValue += currentChar;
                } else {
                    _currentState = START; // End of identifier (Which is just a string realle)
                    tokenFound = true;
                    --_currentPos; // Re-evaluate the character in the next state
                }
                break;
            case NUMBER:
                if (std::isdigit(currentChar)) { // Keep appending as long as its a number
                    tokenValue += currentChar;
                } else {
                    _currentState = START; // Ending number
                    tokenFound = true;
                    --_currentPos; // Re-evaluate this character in the next state
                }
                break;

            // Handle STRING state as well as others
        }
        ++_currentPos;
    }

    if (tokenFound || !tokenValue.empty()) {
        return Token(tokenType, tokenValue);
    }

    return Token(Token::Type::Unknown, "");
}

// Method to return the tokens vector
std::vector<Token> Tokenizer::getTokens() const {
    return _tokens;
}
