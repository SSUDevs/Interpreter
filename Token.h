#ifndef ASSIGNMENT1_460_TOKEN_H
#define ASSIGNMENT1_460_TOKEN_H
#include <iostream>

using namespace std;
class Token
{

public:
     Token();

     // Return the name of the tokens type
     std::string tokenType() { return _tokenType; }

     // Return the identifier used in a declaration of a function or variable
     std::string identifier() { return _identifier; }

     // Grouping and Structure Tokens
     bool &isLParen();
     bool &isRParen();
     bool &isLBracket();
     bool &isRBracket();
     bool &isLBrace();
     bool &isRBrace();

     // Quotation Tokens
     bool &isDoubleQuote();
     bool &isSingleQuote();
     bool &isComma();
     bool &isColon();
     bool &isSemicolon();

     // Numeric and Operational Tokens
     bool &isHexDigit(); // Hex Digit, possibly used with escape characters as a string
     bool &isDigit();
     bool &isAssignmentOperator();
     bool &isPlus();   // Plus, with consideration for its use with integers for addition
     bool &isMinus();  // Minus, also with integer consideration for negative
     bool &isSlash();  // Slash, not necessarily a division operator
     bool &isDivide(); // Explicit Division Operator
     bool &isAsterisk();
     bool &isModulo();
     bool &isCaret();

     // Boolean Expression Tokens
     bool &isLt();
     bool &isGt();
     bool &isLtEqual();
     bool &isGtEqual();
     bool &isBooleanAnd();
     bool &isBooleanOr();
     bool &isBooleanNot();
     bool &isBooleanEqual();
     bool &isBooleanNotEqual();

     // Special Token
     bool &isEscape(); // Used for escape characters

     // Complex Token Types
     bool &isIdentifier(); 

     /* <STRING> ::= <CHARACTER | <ESCAPED_CHARACTER> | <CHARACTER> <STRING> | <ESCAPED_CHARACTER> <STRING> */
     bool &isString();

     /* <SINGLE_QUOTED_STRING> ::= <SINGLE_QUOTE> <STRING> <SINGLE_QUOTE> */
     bool &isSingleQuotedString();

     /* <DOUBLE_QUOTED_STRING> ::= <DOUBLE_QUOTE> <STRING> <DOUBLE_QUOTE> */
     bool &isDoubleQuotedString();

     /* <WHOLE_NUMBER> ::= <DIGIT> | <DIGIT> <WHOLE_NUMBER> */
     bool &isWholeNumber();

     /* <INTEGER> ::= <WHOLE_NUMBER> | <PLUS> <WHOLE_NUMBER> | <MINUS> <WHOLE_NUMBER> */
     bool &isInteger();

     void print();

private:
     // Identifies the token (Either just a name and thus refered to as 'IDENTIFIER' or could be 'INTEGER', 'SEMICOLON' ect...)
     std::string _tokenType;

     // Stores the string that acts as the identifier of a variable, function ect... (NOT A STRING LITERAL)
     std::string _identifier;

     // Stores the string the string literal if applicable like printf ("Fizz") where Fizz is the string
     std::string _name;

     // Grouping and Structure Tokens
     bool _isLParen, _isRParen, _isOpenCurlyBrace, _isCloseCurlyBrace,
         _isLBracket, _isRBracket, _isLBrace, _isRBrace;

     // Quotation and Delimiter Tokens
     bool _isDoubleQuote, _isSingleQuote, _isComma, _isColon, _isSemicolon;

     // Numeric and Operational Tokens
     bool _isWholeNumber, _isHexDigit, _isDigit, _isAssignmentOperator, _isPlus, _isMinus,
         _isSlash, _isDivide, _isAsterisk, _isModulo, _isCaret;

     // Boolean Expression Tokens
     bool _isLt, _isGt, _isLtEqual, _isGtEqual,
         _isBooleanAnd, _isBooleanOr, _isBooleanNot,
         _isBooleanEqual, _isBooleanNotEqual;

     // Special Token
     bool _isEscape, _isInteger, _isString, _isIdentifier;

     // Complex Token Types
     bool _isSingleQuotedString, _isDoubleQuotedString;
};

#endif // ASSIGNMENT1_460_TOKEN_H