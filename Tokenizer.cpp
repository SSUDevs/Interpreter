#include "Tokenizer.h"
#include "Token.h"
#include <vector>

// Pass in the vector created from fileAsArray that has parsed out comments to initialize the Tokenizer
Tokenizer::Tokenizer(std::vector<char> file)
{
    _file = file; // NOTE: This is a COPY and will NOT reference the underline array in fileAsArray
}

bool Tokenizer::charOfInterest(char c)
{
    // Returns true if token found, false otherwise.
    // All tokens should be listed here, if not please update!
    return (c == '{') || (c == '}') ||
           (c == '[') || (c == ']') ||
           (c == '(') || (c == ')') ||
           (c == ',') || (c == ':') ||
           (c == ';') || (c == '+') ||
           (c == '-') || (c == '/') ||
           (c == '*') || (c == '%') ||
           (c == '^') || (c == '<') ||
           (c == '>') || (c == '=') || // Note: '=' is part of '==', '<=', '>=', '!='
           (c == '!') ||               // Note: '!' is part of '!='
           (c == '&') ||               // Note: '&' is part of '&&'
           (c == '|') ||               // Note: '|' is part of '||'
           (c == '"') ||               // Double quote
           (c == '\'');                // Single quote
}

Token Tokenizer::getToken()
{
    char c; // Used to hold each char read from vector

    if (_file.empty())
    {
        std::cout << "Tokenizer::getToken() called with a empty vector." << std::endl;
        exit(2);
    }

    while (!charOfInterest(_file[currentPos]))
    {
        // Skip chars until a character of interest is found
        // and when this happens break out of loop.

        // If space found then skip next char i:e "
        currentPos++;
    }

    // Use Token Constructor
    Token token;

    if (_file.empty())
    {
        return token; // Return default token
    }

    // Now, we can go through a sequence of if ... else if statements
    // to identify the token whose first character we have just read. This is
    // the character that caused the while loop to terminate.

    /*
        DFA goes here
    */

    else
    {
        // This should'nt never be executed
        std::cout << "There is a logic error in function Tokenizer::getToken.\n";
        std::cout << "The function doesn't know how to process this character: ->" << c << "<-\n";
        exit(1);
    }

    return token; // The control SHOULD NOT reach this statement.
}