//
// Created by Luis carmona on 2/7/24.
//

#ifndef ASSIGNMENT1_460_TOKEN_H
#define ASSIGNMENT1_460_TOKEN_H
#include <iostream>

using namespace std;
class Token
{

public:
    Token();

    // Grouping and Structure Tokens
    bool &isLParen();          
    bool &isRParen();             
    bool &isOpenCurlyBrace();    
    bool &isCloseCurlyBrace();    
    bool &isOpenSquareBracket(); 
    bool &isCloseSquareBracket(); 
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
    bool &endOfFile();
   
    // Complex Token Types

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
    // Grouping and Structure Tokens
    bool _isLParen, _isRParen, _isOpenCurlyBrace, _isCloseCurlyBrace,
         _isOpenSquareBracket, _isCloseSquareBracket, _isLBrace, _isRBrace;
    
    // Quotation and Delimiter Tokens
    bool _isDoubleQuote, _isSingleQuote, _isComma, _isColon, _isSemicolon;

    // Numeric and Operational Tokens
    bool _isHexDigit, _isDigit, _isAssignmentOperator, _isPlus, _isMinus,
         _isSlash, _isDivide, _isAsterisk, _isModulo, _isCaret;

    // Boolean Expression Tokens
    bool _isLt, _isGt, _isLtEqual, _isGtEqual,
         _isBooleanAnd, _isBooleanOr, _isBooleanNot,
         _isBooleanEqual, _isBooleanNotEqual;

    // Special Token
    bool _isEscape, _endOfFile;

    // Complex Token Types
    bool _isString, _isSingleQuotedString, _isDoubleQuotedString,
         _isWholeNumber, _isInteger;
};

#endif // ASSIGNMENT1_460_TOKEN_H
int state = 0;
