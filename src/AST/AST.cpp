//
// Created by Luis carmona on 4/8/24.
//

#include "AST.hpp"
#include "../Token/Token.h"

vector<Node> inToPostFix (const vector<Node>& inFix) {
    vector<Node> stack;
    vector<Node> postFix;

    for (int i = 0; i < inFix.size(); ++i) {
        Token::Type tokType = inFix[i].value.type();

        if (tokType == Token::Type::Integer ||
            tokType == Token::Type::Identifier ||
            tokType == Token::Type::SingleQuotedString ||
            tokType == Token::Type::DoubleQuotedString ||
            tokType == Token::Type:: LBracket ||
            tokType == Token::Type:: RBracket
            )
        {
            postFix.push_back(inFix[i]);    // display token
        }
        else {
            if (tokType == Token::Type::LParen) {
                stack.push_back(inFix[i]);  // put on stack
            }
            else {
                if (tokType == Token::Type::RParen) {
                    bool finished = false;
                    while (!finished) {
                        if (stack.back().value.type() == Token::Type::LParen) {
                            stack.pop_back();
                            finished = true;
                        }
                        else {
                            postFix.push_back(stack.back());  // display token at top of stack
                            stack.pop_back();
                        }
                    }
                }
                else {
                    if (tokType == Token::Type::AssignmentOperator ||
                        tokType == Token::Type::BooleanEqual ||
                        tokType == Token::Type::BooleanNotEqual ||
                        tokType == Token::Type::Lt ||
                        tokType == Token::Type::Gt ||
                        tokType == Token::Type:: LtEqual ||
                        tokType == Token::Type:: GtEqual ||
                        tokType == Token::Type:: BooleanAnd ||
                        tokType == Token::Type:: BooleanOr ||
                        tokType == Token::Type:: BooleanNot ||
                        tokType == Token::Type:: Plus ||
                        tokType == Token::Type:: Minus ||
                        tokType == Token::Type:: Asterisk ||
                        tokType == Token::Type:: Slash ||
                        tokType == Token::Type:: Modulo
                    )
                    {
                        if (stack.empty()) {
                            stack.push_back(inFix[i]);  // put on stack
                        }
                        else {
                            if (stack.back().value.type() == Token::Type::LParen) {
                                stack.push_back(inFix[i]);  // put on stack
                            }
                            else {
                                if (tokType == Token::Type::BooleanNot) {
                                    bool finished = false;
                                    while (!finished) {
                                        if (!stack.empty()) {
                                            if (stack.back().value.type() == Token::Type::BooleanNot) {
                                                postFix.push_back(stack.back());  // display token at top of stack
                                                stack.pop_back();
                                            }
                                            else {
                                                stack.push_back(inFix[i]);  // put on stack
                                                finished = true;
                                            }
                                        }
                                        else {
                                            stack.push_back(inFix[i]);  // put on stack
                                            finished = true;
                                        }
                                    }
                                }
                                else {
                                    if (tokType == Token::Type::Asterisk ||
                                        tokType == Token::Type::Slash ||
                                        tokType == Token::Type::Modulo
                                        )
                                    {
                                        bool finished = false;
                                        while (!finished) {
                                            if (!stack.empty()) {
                                                if (stack.back().value.type() == Token::Type::BooleanNot ||
                                                    stack.back().value.type() == Token::Type::Asterisk ||
                                                    stack.back().value.type() == Token::Type::Slash ||
                                                    stack.back().value.type() == Token::Type::Modulo
                                                    )
                                                {
                                                    postFix.push_back(stack.back());  // display token at top of stack
                                                    stack.pop_back();
                                                }
                                                else {
                                                    stack.push_back(inFix[i]);  // put on stack
                                                    finished = true;
                                                }
                                            }
                                            else {
                                                stack.push_back(inFix[i]);  // put on stack
                                                finished = true;
                                            }
                                        }
                                    }
                                    else {
                                        if (tokType == Token::Type::Plus || tokType == Token::Type::Minus) {
                                            bool finished = false;
                                            while (!finished) {
                                                if (!stack.empty()){
                                                    if (stack.back().value.type() == Token::Type::BooleanNot ||
                                                        stack.back().value.type() == Token::Type::Asterisk ||
                                                        stack.back().value.type() == Token::Type::Slash ||
                                                        stack.back().value.type() == Token::Type::Modulo ||
                                                        stack.back().value.type() == Token::Type::Plus ||
                                                        stack.back().value.type() == Token::Type::Minus
                                                    )
                                                    {
                                                        postFix.push_back(stack.back());  // display token at top of stack
                                                        stack.pop_back();
                                                    }
                                                    else {
                                                        stack.push_back(inFix[i]);  // put on stack
                                                        finished = true;
                                                    }
                                                }
                                                else {
                                                    stack.push_back(inFix[i]);  // put on stack
                                                    finished = true;
                                                }
                                            }
                                        }
                                        else {
                                            if (tokType == Token::Type::BooleanAnd) {
                                                bool finished = false;
                                                while (!finished) {
                                                    if (!stack.empty()) {
                                                        if (stack.back().value.type() == Token::Type::BooleanNot ||
                                                            stack.back().value.type() == Token::Type::Asterisk ||
                                                            stack.back().value.type() == Token::Type::Slash ||
                                                            stack.back().value.type() == Token::Type::Modulo ||
                                                            stack.back().value.type() == Token::Type::Plus ||
                                                            stack.back().value.type() == Token::Type::Minus ||
                                                            stack.back().value.type() == Token::Type::BooleanEqual ||
                                                            stack.back().value.type() == Token::Type::BooleanNotEqual ||
                                                            stack.back().value.type() == Token::Type::Lt ||
                                                            stack.back().value.type() == Token::Type::Gt ||
                                                            stack.back().value.type() == Token::Type:: LtEqual ||
                                                            stack.back().value.type() == Token::Type:: GtEqual ||
                                                            stack.back().value.type() == Token::Type:: BooleanAnd ||
                                                            stack.back().value.type() == Token::Type:: BooleanOr
                                                        )
                                                        {
                                                            postFix.push_back(stack.back());  // display token at top of stack
                                                            stack.pop_back();
                                                        }
                                                        else {
                                                            stack.push_back(inFix[i]);  // put on stack
                                                            finished = true;
                                                        }
                                                    }
                                                    else {
                                                        stack.push_back(inFix[i]);  // put on stack
                                                        finished = true;
                                                    }
                                                }
                                            }
                                            else {
                                                if (tokType == Token::Type::BooleanOr) {
                                                    bool finished = false;
                                                    while (!finished) {
                                                        if (!stack.empty()) {
                                                            if (stack.back().value.type() == Token::Type::BooleanNot ||
                                                                stack.back().value.type() == Token::Type::Asterisk ||
                                                                stack.back().value.type() == Token::Type::Slash ||
                                                                stack.back().value.type() == Token::Type::Modulo ||
                                                                stack.back().value.type() == Token::Type::Plus ||
                                                                stack.back().value.type() == Token::Type::Minus ||
                                                                stack.back().value.type() == Token::Type::BooleanEqual ||
                                                                stack.back().value.type() == Token::Type::BooleanNotEqual ||
                                                                stack.back().value.type() == Token::Type::Lt ||
                                                                stack.back().value.type() == Token::Type::Gt ||
                                                                stack.back().value.type() == Token::Type:: LtEqual ||
                                                                stack.back().value.type() == Token::Type:: GtEqual ||
                                                                stack.back().value.type() == Token::Type:: BooleanAnd ||
                                                                stack.back().value.type() == Token::Type:: BooleanOr
                                                            )
                                                            {
                                                                postFix.push_back(stack.back());  // display token at top of stack
                                                                stack.pop_back();
                                                            }
                                                            else {
                                                                stack.push_back(inFix[i]);  // put on stack
                                                                finished = true;
                                                            }
                                                        }
                                                        else {
                                                            stack.push_back(inFix[i]);  // put on stack
                                                            finished = true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    while (!stack.empty()) {
        postFix.push_back(stack.back());  // display token at top of stack
        stack.pop_back();
    }

    return postFix;
}