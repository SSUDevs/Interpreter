#include "Token.h"

std::string Token::typeToString(Type type) {
    switch (type) {
    case Type::LParen:
        return "LEFT_PARENTHESIS";
    case Type::RParen:
        return "RIGHT_PARENTHESIS";
    case Type::LBracket:
        return "LEFT_BRACKET";
    case Type::RBracket:
        return "RIGHT_BRACKET";
    case Type::LBrace:
        return "LEFT_BRACE";
    case Type::RBrace:
        return "RIGHT_BRACE";
    case Type::DoubleQuote:
        return "DOUBLE_QUOTE";
    case Type::SingleQuote:
        return "SINGLE_QUOTE";
    case Type::Comma:
        return "COMMA";
    case Type::Colon:
        return "COLON";
    case Type::Semicolon:
        return "SEMICOLON";
    case Type::HexDigit:
        return "HEX_DIGIT";
    case Type::Digit:
        return "DIGIT";
    case Type::AssignmentOperator:
        return "ASSIGNMENT";
    case Type::Plus:
        return "PLUS";
    case Type::Minus:
        return "MINUS";
    case Type::Slash:
        return "SLASH";
    case Type::Asterisk:
        return "ASTERISK";
    case Type::Modulo:
        return "MODULO";
    case Type::Caret:
        return "CARET";
    case Type::If:
        return "IF";
    case Type::Lt:
        return "LESS_THAN";
    case Type::Gt:
        return "GREATER_THAN";
    case Type::LtEqual:
        return "LESS_THAN_OR_EQUAL";
    case Type::GtEqual:
        return "GREATER_THAN_OR_EQUAL";
    case Type::BooleanAnd:
        return "BOOLEAN_AND";
    case Type::BooleanOr:
        return "BOOLEAN_OR";
    case Type::BooleanNot:
        return "BOOLEAN_NOT";
    case Type::BooleanEqual:
        return "BOOLEAN_EQUAL";
    case Type::BooleanNotEqual:
        return "BOOLEAN_NOT_EQUAL";
    case Type::BooleanTrue:
        return "BOOLEAN_TRUE";
    case Type::BooleanFalse:
        return "BOOLEAN_False";
    case Type::Escape:
        return "ESCAPE";
    case Type::Identifier:
        return "IDENTIFIER";
    case Type::String:
        return "STRING";
    case Type::SingleQuotedString:
        return "SINGLE_QUOTED_STRING";
    case Type::DoubleQuotedString:
        return "DOUBLE_QUOTED_STRING";
    case Type::WholeNumber:
        return "WHOLE_NUMBER";
    case Type::Integer:
        return "INTEGER";
    case Type::Return:
        return "RETURN";
    case Type::Unknown:
        return "UNKNOWN";
    default:
        return "INVALID_TYPE"; // In case a new type is added and not handled
    }
}

// Print the token type and value in the specified format
void Token::print() const {
    std::cout << "Token type: " << typeToString(_type) << std::endl;
    std::cout << "Token:      " << _value << std::endl;
    std::cout << "Line: " << _lineNum << std::endl
              << std::endl; // Added a line break for spacing
}