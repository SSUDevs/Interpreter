#include "Tokenizer.h"
#include <iostream>
#include <sstream>

Tokenizer::Tokenizer(const std::vector<char> &file)
    : _file(file), _size(file.size()) {}

bool Tokenizer::isOperator(Token t) {

    std::string value = t.value();

    if (value == "+" || value == "-" || value == "*" || value == "/" ||
        value == "%" || value == "^" || value == "=")
        return true;
    return false;
}

bool Tokenizer::isOperator(char value) {

    if (value == '+' || value == '-' || value == '*' || value == '/' ||
        value == '%' || value == '^' || value == '=')
        return true;
    return false;
}

void Tokenizer::tokenizeVector() {
    _currentPos = 0;
    _currentState = START;
    while (_currentPos < _size) {
        Token token = getToken(); // Gonna get the next token
        if (token.type() !=
            Token::Type::Unknown) { // Skipping unknown tokens for now
            _tokens.push_back(token);
        }
    }
}

Token Tokenizer::getToken() {
    std::string tokenValue;
    Token::Type tokenType = Token::Type::Unknown;
    size_t tokenLineNum = _lineNum;
    bool tokenFound = false;

    while (_currentPos < _size && !tokenFound) {

        char currentChar = _file[_currentPos];
        switch (_currentState) {
        case START:
            if (currentChar == '\n') {
                tokenLineNum++;
            } else if (std::isspace(currentChar)) {
                // Ignore whitespace
            } else if (std::isalpha(currentChar)) {
                tokenType = Token::Type::Identifier;
                _currentState = IDENTIFIER;
                tokenValue += currentChar;
            } else if (std::isdigit(currentChar)) {
                tokenType = Token::Type::Integer; // I think needs to be updated
                // cause a sign could come
                // before (so for ints)
                _currentState = INTEGER;
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
                case '[':
                    tokenType = Token::Type::LBracket;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case ']':
                    tokenType = Token::Type::RBracket;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '{':
                    tokenType = Token::Type::LBrace;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '}':
                    tokenType = Token::Type::RBrace;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '"':
                    tokenValue += currentChar;
                    _currentState = DQ_STRING;
                    break;
                case '\'':
                    tokenValue += currentChar;
                    _currentState = SQ_STRING;
                    break;
                case ';':
                    tokenType = Token::Type::Semicolon;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case ',':
                    tokenType = Token::Type::Comma;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '*':
                    tokenType = Token::Type::Asterisk;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '/':
                    tokenType = Token::Type::Slash;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '%':
                    tokenType = Token::Type::Modulo;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '^':
                    tokenType = Token::Type::Caret;
                    tokenValue = currentChar;
                    tokenFound = true;
                    break;
                case '<':
                    if (_currentPos + 1 < _size &&
                        _file[_currentPos + 1] == '=') {
                        tokenType = Token::Type::LtEqual;
                        tokenValue = "<=";
                        tokenFound = true;
                        ++_currentPos;
                    } else {
                        tokenType = Token::Type::Lt;
                        tokenValue = "<";
                        tokenFound = true;
                    }
                    break;
                case '>':
                    if (_currentPos + 1 < _size &&
                        _file[_currentPos + 1] == '=') {
                        tokenType = Token::Type::GtEqual;
                        tokenValue = ">=";
                        tokenFound = true;
                        ++_currentPos;
                    } else {
                        tokenType = Token::Type::Gt;
                        tokenValue = ">";
                        tokenFound = true;
                    }
                    break;
                case '&':
                    if (_currentPos + 1 < _size &&
                        _file[_currentPos + 1] == '&') {
                        tokenType = Token::Type::BooleanAnd;
                        tokenValue = "&&";
                        tokenFound = true;
                        ++_currentPos;
                    }
                    break;

                case '|':
                    if (_currentPos + 1 < _size &&
                        _file[_currentPos + 1] == '|') {
                        tokenType = Token::Type::BooleanOr;
                        tokenValue = "||";
                        tokenFound = true;
                        ++_currentPos;
                    }
                    break;
                case '!':
                    if (_currentPos + 1 < _size &&
                        _file[_currentPos + 1] == '=') {
                        tokenType = Token::Type::BooleanNotEqual;
                        tokenValue = "!=";
                        tokenFound = true;
                        ++_currentPos;
                    } else {
                        tokenType = Token::Type::BooleanNot;
                        tokenValue = "!";
                        tokenFound = true;
                    }
                    break;
                case '=':
                    if (_currentPos + 1 < _size &&
                        _file[_currentPos + 1] == '=') {
                        tokenType = Token::Type::BooleanEqual;
                        tokenValue = "==";
                        tokenFound = true;
                        ++_currentPos;
                    } else {
                        tokenType = Token::Type::AssignmentOperator;
                        tokenValue = "=";
                        tokenFound = true;
                    }
                    break;
                case '+':
                case '-':
                    // check if last token was an op
                    if (isOperator(_tokens.back()) ||
                        _tokens.back().value() == "("
                        || _tokens.back().value() == "[") {
                        // Treat as part of an integer if appropriate
                        tokenType = Token::Type::Integer;
                        tokenValue += currentChar;
                        _currentState = INTEGER; // Continue to INTEGER state to
                        // allow for digits to follow
                    } else {
                        // Use ternary op to choose sign
                        tokenType = (currentChar == '+') ? Token::Type::Plus
                                                         : Token::Type::Minus;
                        tokenValue = currentChar;
                        tokenFound = true;
                    }
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
                /*if (tokenValue == "if") {
                    tokenType = Token::Type::If; 
                } else if (tokenValue == "else") {
                    tokenType = Token::Type::Else;
                } else if (tokenValue == "return") {
                    tokenType = Token::Type::Return;
                } */if (tokenValue == "TRUE") {
                    tokenType = Token::Type::BooleanTrue;
                } else if (tokenValue == "FALSE") {
                    tokenType = Token::Type::BooleanFalse;
                }
                _currentState = START;
                tokenFound = true;
                --_currentPos; // Re-evaluate the character in the next state
            }
            break;
        case INTEGER:

            // in case integer starts signed (pos/neg) and the current char is
            // not a digit
            if ((tokenValue.back() == '+' || tokenValue.back() == '-') &&
                !isdigit(currentChar)) {
                std::cerr << "Syntax error on line " << _lineNum
                          << ": invalid signed integer\n";
                exit(1);
            }

            if (std::isdigit(
                    currentChar)) { // Keep appending as long as its a number
                tokenValue += currentChar;
            } else if (!(isOperator(currentChar) || isspace(currentChar) ||
                         currentChar == ';' || currentChar == ')' || currentChar ==']') ||
                       isalpha(currentChar)) {
                std::cerr << "Syntax error on line " << _lineNum
                          << ": invalid Integer\n";
                exit(1);
            } else {
                _currentState = START; // Ending number
                tokenFound = true;
                --_currentPos; // Re-evaluate this character in the next state
            }
            break;
        case DQ_STRING:
            if (currentChar == '"') {
                // if the previous character was a backslash don't count this quote as a quote
                if (_file[_currentPos - 1] == '\\') {
                    tokenValue += currentChar;
                }
                else {
                    if (tokenValue.length() == 1) {

                        tokenType = Token::Type::DoubleQuote;
                    } else {

                        tokenType = Token::Type::DoubleQuotedString;
                    }
                    tokenFound = true;
                    tokenValue += currentChar;
                    _currentState = START;
                }
            } else {
                if (currentChar == '\n') {
                    std::cerr << "Unterminated string quote on line: " << _lineNum << std::endl;
                    exit(99);
                }
                tokenValue += currentChar;
            }
            break;
       
        case SQ_STRING:
            if (currentChar == '\'') {
                if (_file[_currentPos - 1] == '\\') {
                    tokenValue += currentChar;
                }
                else {
                    if (tokenValue.length() == 1) {

                        tokenType = Token::Type::SingleQuote;
                    } else {

                        tokenType = Token::Type::SingleQuotedString;
                    }
                    tokenFound = true;
                    tokenValue += currentChar;
                    _currentState = START;
                }
            } else {
                if (currentChar == '\n') {
                    std::cerr << "Unterminated string quote on line: " << _lineNum << std::endl;
                    exit(99);
                }
                tokenValue += currentChar;
            }
            break;

        }
        ++_currentPos;
    }

    if (tokenFound || !tokenValue.empty()) {
        _lineNum = tokenLineNum;
        return Token(tokenType, tokenValue, tokenLineNum);
    }

    return Token(Token::Type::Unknown, "", -1);
}

// Method to return the tokens vector
std::vector<Token> Tokenizer::getTokens() const { return _tokens; }
