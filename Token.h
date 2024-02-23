#ifndef INTERPRETER_TOKEN_H
#define INTERPRETER_TOKEN_H

#include <iostream>
#include <string>

class Token {
public:
    // Define an enum class for token types
    enum class Type {
        LParen, RParen, LBracket, RBracket, LBrace, RBrace,
        DoubleQuote, SingleQuote, Comma, Colon, Semicolon,
        HexDigit, Digit, AssignmentOperator, Plus, Minus,
        Slash, Asterisk, Modulo, Caret,
        Lt, Gt, LtEqual, GtEqual,
        BooleanAnd, BooleanOr, BooleanNot,
        BooleanEqual, BooleanNotEqual,
        Escape, Identifier, String,
        SingleQuotedString, DoubleQuotedString,
        WholeNumber, Integer,
        Unknown // For unrecognized tokens
    };

private:
    Type _type;
    std::string _value;

public:
    Token(Type type, const std::string& value) : _type(type), _value(value) {}

    // Accessors functions
    Type type() const { return _type; }

    // Function to convert Type to a readable string
    static std::string typeToString(Type type);

    void print() const;
};

#endif // INTERPRETER_TOKEN_H
