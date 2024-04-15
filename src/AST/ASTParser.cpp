#include "ASTParser.h"
#include <iostream>
#include <string>

using namespace std;

ASTParser::ASTParser(const NodePtr &cstRoot)
    : currCstNode(cstRoot), root(nullptr), lastASTNode(nullptr) {}

NodePtr ASTParser::parse() {
    while (currCstNode) {
        // Get the string token value stored in the cst node
        string cstNodeValue = currCstNode->Value().value();
        // Determine the semantic type and set it while creating root node
        Node::Type type = determineSemanticNodeType(cstNodeValue);
        // Create a new node with the same value and updated "type"
        auto newNode = make_shared<Node>(currCstNode->Value(), type);

        // Add as child or sibling based on the type
        if (type != Node::Type::OTHER) {
            addToAST(newNode, LeftChild);
        }

        // Move to the next important node
        while (currCstNode->Right()) {
            currCstNode = getNextCSTNode();
        }

        // Drop into the important node of the CST
        currCstNode = currCstNode->Left();
    }
    return root;
}

NodePtr ASTParser::getNextCSTNode() {
    return currCstNode ? (currCstNode->Right() ? currCstNode->Right()
                                               : currCstNode->Left())
                       : nullptr;
}

void ASTParser::addToAST(NodePtr node, InsertionMode mode) {
    if (!root) {
        root = node;
    } else {
        if (mode == LeftChild)
            lastASTNode->leftChild = node;
        else
            lastASTNode->rightSibling = node;
    }
    lastASTNode = node;
}

Node::Type ASTParser::determineSemanticNodeType(const std::string &value) {
    if (value == "function" || value == "procedure" || isDataType(value)) {
        return Node::Type::DECLARATION;
    } else if (value == "{") {
        return Node::Type::BEGIN_BLOCK;
    } else if (value == "}") {
        return Node::Type::END_BLOCK;
    } else if (value == "if") {
        return Node::Type::IF;
    } else if (value == "else") {
        return Node::Type::ELSE;
    } else if (value == "for") {
        return Node::Type::FOR;
    } else if (value == "while") {
        return Node::Type::WHILE;
    } else if (value == "printf") {
        return Node::Type::PRINTF;
    } else if (value == "return") {
        return Node::Type::RETURN;
    }
    return Node::Type::OTHER; // Default type if none of the conditions match
}

bool ASTParser::isDataType(string id) {
    if (id == "char" || id == "int" || id == "bool")
        return true;
    return false;
}

vector<Node> ASTParser::inToPostFix(const std::vector<Node> &inFix) {
    vector<Node> stack;
    vector<Node> postFix;

    for (int i = 0; i < inFix.size(); ++i) {
        Token::Type tokType = inFix[i].value.type();

        if (tokType == Token::Type::Integer ||
            tokType == Token::Type::Identifier ||
            tokType == Token::Type::SingleQuotedString ||
            tokType == Token::Type::DoubleQuotedString ||
            tokType == Token::Type::LBracket ||
            tokType == Token::Type::RBracket) {
            postFix.push_back(inFix[i]); // display token
        } else {
            if (tokType == Token::Type::LParen) {
                stack.push_back(inFix[i]); // put on stack
            } else {
                if (tokType == Token::Type::RParen) {
                    bool finished = false;
                    while (!finished) {
                        if (stack.back().value.type() == Token::Type::LParen) {
                            stack.pop_back();
                            finished = true;
                        } else {
                            postFix.push_back(
                                stack.back()); // display token at top of stack
                            stack.pop_back();
                        }
                    }
                } else {
                    if (tokType == Token::Type::AssignmentOperator ||
                        tokType == Token::Type::BooleanEqual ||
                        tokType == Token::Type::BooleanNotEqual ||
                        tokType == Token::Type::Lt ||
                        tokType == Token::Type::Gt ||
                        tokType == Token::Type::LtEqual ||
                        tokType == Token::Type::GtEqual ||
                        tokType == Token::Type::BooleanAnd ||
                        tokType == Token::Type::BooleanOr ||
                        tokType == Token::Type::BooleanNot ||
                        tokType == Token::Type::Plus ||
                        tokType == Token::Type::Minus ||
                        tokType == Token::Type::Asterisk ||
                        tokType == Token::Type::Slash ||
                        tokType == Token::Type::Modulo) {
                        if (stack.empty()) {
                            stack.push_back(inFix[i]); // put on stack
                        } else {
                            if (stack.back().value.type() ==
                                Token::Type::LParen) {
                                stack.push_back(inFix[i]); // put on stack
                            } else {
                                if (tokType == Token::Type::BooleanNot) {
                                    bool finished = false;
                                    while (!finished) {
                                        if (!stack.empty()) {
                                            if (stack.back().value.type() ==
                                                Token::Type::BooleanNot) {
                                                postFix.push_back(
                                                    stack.back()); // display
                                                                   // token at
                                                                   // top of
                                                                   // stack
                                                stack.pop_back();
                                            } else {
                                                stack.push_back(
                                                    inFix[i]); // put on stack
                                                finished = true;
                                            }
                                        } else {
                                            stack.push_back(
                                                inFix[i]); // put on stack
                                            finished = true;
                                        }
                                    }
                                } else {
                                    if (tokType == Token::Type::Asterisk ||
                                        tokType == Token::Type::Slash ||
                                        tokType == Token::Type::Modulo) {
                                        bool finished = false;
                                        while (!finished) {
                                            if (!stack.empty()) {
                                                if (stack.back().value.type() ==
                                                        Token::Type::
                                                            BooleanNot ||
                                                    stack.back().value.type() ==
                                                        Token::Type::Asterisk ||
                                                    stack.back().value.type() ==
                                                        Token::Type::Slash ||
                                                    stack.back().value.type() ==
                                                        Token::Type::Modulo) {
                                                    postFix.push_back(
                                                        stack
                                                            .back()); // display
                                                                      // token
                                                                      // at top
                                                                      // of
                                                                      // stack
                                                    stack.pop_back();
                                                } else {
                                                    stack.push_back(
                                                        inFix[i]); // put on
                                                                   // stack
                                                    finished = true;
                                                }
                                            } else {
                                                stack.push_back(
                                                    inFix[i]); // put on stack
                                                finished = true;
                                            }
                                        }
                                    } else {
                                        if (tokType == Token::Type::Plus ||
                                            tokType == Token::Type::Minus) {
                                            bool finished = false;
                                            while (!finished) {
                                                if (!stack.empty()) {
                                                    if (stack.back()
                                                                .value.type() ==
                                                            Token::Type::
                                                                BooleanNot ||
                                                        stack.back()
                                                                .value.type() ==
                                                            Token::Type::
                                                                Asterisk ||
                                                        stack.back()
                                                                .value.type() ==
                                                            Token::Type::
                                                                Slash ||
                                                        stack.back()
                                                                .value.type() ==
                                                            Token::Type::
                                                                Modulo ||
                                                        stack.back()
                                                                .value.type() ==
                                                            Token::Type::Plus ||
                                                        stack.back()
                                                                .value.type() ==
                                                            Token::Type::
                                                                Minus) {
                                                        postFix.push_back(
                                                            stack
                                                                .back()); // display
                                                                          // token
                                                                          // at
                                                                          // top
                                                                          // of
                                                                          // stack
                                                        stack.pop_back();
                                                    } else {
                                                        stack.push_back(
                                                            inFix[i]); // put on
                                                                       // stack
                                                        finished = true;
                                                    }
                                                } else {
                                                    stack.push_back(
                                                        inFix[i]); // put on
                                                                   // stack
                                                    finished = true;
                                                }
                                            }
                                        } else {
                                            if (tokType ==
                                                Token::Type::BooleanAnd) {
                                                bool finished = false;
                                                while (!finished) {
                                                    if (!stack.empty()) {
                                                        if (stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanNot ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Asterisk ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Slash ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Modulo ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Plus ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Minus ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanEqual ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanNotEqual ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Lt ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Gt ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    LtEqual ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    GtEqual ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanAnd ||
                                                            stack.back()
                                                                    .value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanOr) {
                                                            postFix.push_back(
                                                                stack
                                                                    .back()); // display token at top of stack
                                                            stack.pop_back();
                                                        } else {
                                                            stack.push_back(
                                                                inFix
                                                                    [i]); // put
                                                                          // on
                                                                          // stack
                                                            finished = true;
                                                        }
                                                    } else {
                                                        stack.push_back(
                                                            inFix[i]); // put on
                                                                       // stack
                                                        finished = true;
                                                    }
                                                }
                                            } else {
                                                if (tokType ==
                                                    Token::Type::BooleanOr) {
                                                    bool finished = false;
                                                    while (!finished) {
                                                        if (!stack.empty()) {
                                                            if (stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanNot ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Asterisk ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Slash ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Modulo ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Plus ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Minus ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanEqual ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanNotEqual ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Lt ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Gt ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        LtEqual ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        GtEqual ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanAnd ||
                                                                stack.back()
                                                                        .value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanOr) {
                                                                postFix.push_back(
                                                                    stack
                                                                        .back()); // display token at top of stack
                                                                stack
                                                                    .pop_back();
                                                            } else {
                                                                stack.push_back(
                                                                    inFix
                                                                        [i]); // put on stack
                                                                finished = true;
                                                            }
                                                        } else {
                                                            stack.push_back(
                                                                inFix
                                                                    [i]); // put
                                                                          // on
                                                                          // stack
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
        postFix.push_back(stack.back()); // display token at top of stack
        stack.pop_back();
    }

    return postFix;
}