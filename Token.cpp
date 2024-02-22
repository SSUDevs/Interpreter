#include "Token.h"

Token::Token()
    : _isLParen(false), _isRParen(false), _isLBracket(false), _isRBracket(false), _isLBrace(false), _isRBrace(false),
      _isDoubleQuote(false), _isSingleQuote(false), _isComma(false), _isColon(false), _isSemicolon(false),
      _isHexDigit(false), _isDigit(false), _isAssignmentOperator(false), _isPlus(false), _isMinus(false),
      _isSlash(false), _isDivide(false), _isAsterisk(false), _isModulo(false), _isCaret(false),
      _isLt(false), _isGt(false), _isLtEqual(false), _isGtEqual(false), _isBooleanAnd(false),
      _isBooleanOr(false), _isBooleanNot(false), _isBooleanEqual(false), _isBooleanNotEqual(false),
      _isEscape(false), _isString(false), _isSingleQuotedString(false), _isDoubleQuotedString(false),
      _isWholeNumber(false), _isInteger(false), _tokenType("") // Default for all token types is an empty string
{
}

// Getter Functions
// Grouping and Structure Tokens
bool &Token::isLParen() { return _isLParen; }
bool &Token::isRParen() { return _isRParen; }
bool &Token::isLBracket() { return _isLBracket; }
bool &Token::isRBracket() { return _isRBracket; }
bool &Token::isLBrace() { return _isLBrace; }
bool &Token::isRBrace() { return _isRBrace; }

// Quotation Tokens
bool &Token::isDoubleQuote() { return _isDoubleQuote; }
bool &Token::isSingleQuote() { return _isSingleQuote; }
bool &Token::isComma() { return _isComma; }
bool &Token::isColon() { return _isColon; }
bool &Token::isSemicolon() { return _isSemicolon; }

// Numeric and Operational Tokens
bool &Token::isHexDigit() { return _isHexDigit; }
bool &Token::isWholeNumber() { return _isWholeNumber; }
bool &Token::isAssignmentOperator() { return _isAssignmentOperator; }
bool &Token::isPlus() { return _isPlus; }
bool &Token::isMinus() { return _isMinus; }
bool &Token::isSlash() { return _isSlash; }
bool &Token::isDivide() { return _isDivide; }
bool &Token::isAsterisk() { return _isAsterisk; }
bool &Token::isModulo() { return _isModulo; }
bool &Token::isCaret() { return _isCaret; }

// Boolean Expression Tokens
bool &Token::isLt() { return _isLt; }
bool &Token::isGt() { return _isGt; }
bool &Token::isLtEqual() { return _isLtEqual; }
bool &Token::isGtEqual() { return _isGtEqual; }
bool &Token::isBooleanAnd() { return _isBooleanAnd; }
bool &Token::isBooleanOr() { return _isBooleanOr; }
bool &Token::isBooleanNot() { return _isBooleanNot; }
bool &Token::isBooleanEqual() { return _isBooleanEqual; }
bool &Token::isBooleanNotEqual() { return _isBooleanNotEqual; }

// Special Tokens
bool &Token::isEscape() { return _isEscape; }  

bool &Token::isInteger() { return _isInteger; }
/* 
    If Input is:
    counter = -2;

    Expected Ouput would be:
    Token type: INTEGER
    Token:      -2
*/
bool &Token::isString() { return _isString; } // This will be known as an IDENTIFIER for the _tokenType
bool &Token::isDigit() { return _isDigit; } // I place this here becuase they inflict upon eachother in this case
/* 
    If Input is:
    1counter = 2;

    Expected Ouput would be:
    Syntax error on line #: invalid integer
*/

// NOTE: 
// The types below aren't really needful of implementation as of yet
// for we are only printing single tokens which can be rep. by the above

// Complex Token Types 
bool &Token::isSingleQuotedString() { return _isSingleQuotedString; }
bool &Token::isDoubleQuotedString() { return _isDoubleQuotedString; }

void Token::print()
{
    if (isLParen())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "(" << endl;
    }
    if (isRParen())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << ")" << endl;
    }
    if (isLBracket())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "{" << endl;
    }
    if (isRBracket())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "}" << endl;
    }
    if (isLBrace())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "[" << endl;
    }
    if (isRBrace())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "]" << endl; 
    }
    if (isDoubleQuote())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "\"" << endl;
    }
    if (isSingleQuote())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "\"" << endl;
    }
    if (isComma())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "," << endl;
    }
    if (isColon())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << ":" << endl;
    }
    if (isSemicolon())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << ";" << endl;
    }
    if (isPlus())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "+" << endl;
    }
    if (isMinus())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "-" << endl;
    }
    if (isDivide() || isSlash())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "/" << endl;
    }
    if (isAsterisk())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "*" << endl;
    }
    if (isModulo())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "%" << endl;
    }
    if (isCaret())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "^" << endl;
    }
    if (isLt())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "<" << endl;
    }
    if (isGt())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << ">" << endl;
    }
    if (isLtEqual())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "<=" << endl;
    }
    if (isGtEqual())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << ">=" << endl;
    }
    if (isBooleanAnd())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "&&" << endl;
    }
    if (isBooleanOr())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "||" << endl;
    }
    if (isBooleanNot())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "!" << endl;
    }
    if (isBooleanEqual())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "==" << endl;
    }
    if (isBooleanNotEqual())
    {
        cout << "Token type: " << tokenType() << endl;
        cout << "Token:      " << "!=" << endl;
    }
    if (isString())
    {
        cout << "Token type: " << tokenType() << endl; 
        cout << "Token:      " << identifier() << endl;
    }
    if (isIdentifier())
    {
        cout << "Token type: " << tokenType() << endl; // Could be hardcoded to 'IDENTIFIER' but whateves lol (I hate harcoding)
        cout << "Token:      " << identifier() << endl;
    }
    // Escape requires slighty more logic that will be added upon implementation
    // if (isEscape())
    // {
    //     cout << '\\' << endl; // Assuming backslash is used for escape but many other chars can be present
    // }

    // These types also need a slightly different approach that needs to be implemented later (For now we are just outputing the single tokens)
    //  isString, isSingleQuotedString, isDoubleQuotedString, isWholeNumber, isInteger,
}
