#include "ASTParser.h"
#include <iostream>
#include <string>
#include <vector>

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

            if (!isDataType(newNode->value.value())) {
            addToAST(newNode, LeftChild);
            }
            if (isDataType(newNode->value.value())) {
                parseTypeDec(currCstNode);
            }
            if (type == Node::Type::IF || type == Node::Type::WHILE) {
                // parse if statements
                currCstNode = currCstNode->Right();
                parseIFsORWhiles(currCstNode);
            } else if (type == Node::Type::PRINTF) {
                currCstNode = currCstNode->Right();
                parsePrintF(currCstNode);
            } else if (type == Node::Type::RETURN) {
                currCstNode = currCstNode->Right(); // skip return
                parseAssignment(currCstNode); // will grab expression and turn
                                              // it into postfix

            } else if (type == Node::Type::FOR) {
                addToAST(make_shared<Node>(currCstNode->Value(),
                                           Node::Type::ForExpression1),
                         LeftChild);
                parseFor(currCstNode);
            }
        } else if (currCstNode->Value().type() == Token::Type::Identifier) {
            // Check for function call
            if (currCstNode->Right()->Value().value() == "(") {
                // Create CALL node
                addToAST(
                    make_shared<Node>(currCstNode->Value(), Node::Type::CALL),
                    LeftChild);

                currCstNode = currCstNode->Right(); // skip (
                currCstNode = currCstNode->Right(); // param

                // Get Params
                while (currCstNode->Value().type() == Token::Type::Identifier) {
                    addToAST(make_shared<Node>(currCstNode->Value(),
                                               Node::Type::OTHER),
                             RightSibling);
                    currCstNode = currCstNode->Right(); // skip , or )
                }
            } else {
                // Must be an assignment op
                addToAST(make_shared<Node>(currCstNode->Value(),
                                           Node::Type::ASSIGNMENT),
                         LeftChild);
                parseAssignment(currCstNode);
            }
        }

        // Move to the next important node
        while (currCstNode->Right() != nullptr) {
            currCstNode = currCstNode->Right();
        }

        // Drop into the important node of the CST
        currCstNode = currCstNode->Left();
    }
    return root;
}
NodePtr ASTParser::parseTypeDec(NodePtr &currCstNode) {
    NodePtr rootSubTreeNode = currCstNode;
    currCstNode= currCstNode->Right();
//    cout<<"In Type Dec "<<currCstNode->Value().value()<<endl;
    //currCstNode = currCstNode->Right();

    while (currCstNode->value.value() != ";") {
//        cout<<"Adding variable with value: "<<currCstNode->Value().value()<<endl;
        if (currCstNode->value.value() != ",") {
        addToAST(make_shared<Node>(currCstNode->Value(),Node::Type::DECLARATION),LeftChild);
        }
        currCstNode = currCstNode->Right();
    }
    return rootSubTreeNode;
}

NodePtr ASTParser::parseFor(NodePtr &currCstNode) {
    // Store the line of nodes in this subtree as a vector
    // Pass it into the function and then add them all in the AST in that orde
    NodePtr rootSubTreeNode = currCstNode;
    std::vector<NodePtr> exp1, exp2, exp3;

    currCstNode = currCstNode->Right(); // skipping first '('
    currCstNode = currCstNode->Right();

    // parse the first expression
    while (currCstNode->value.value() != ";") {
        exp1.push_back(currCstNode);
        currCstNode = currCstNode->Right();
    }
    // change first expression to postfix
    exp1 = inToPostFix(exp1);

    // add first expression
    for (const auto &node : exp1) {
        addToAST(node, RightSibling);
    }

    // parse the second expression
    currCstNode = currCstNode->Right();
    while (currCstNode->value.value() != ";") {
        exp2.push_back(currCstNode);
        currCstNode = currCstNode->Right();
    }
    // change second expression to postfix
    exp2 = inToPostFix(exp2);

    // add second expressiont to AST
    addToAST(
        make_shared<Node>(currCstNode->Value(), Node::Type::ForExpression2),
        LeftChild);
    for (const auto &node : exp2) {
        addToAST(node, RightSibling);
    }

    // parse the third express
    while (currCstNode->value.value() != ")") {
        exp3.push_back(currCstNode);
        currCstNode = currCstNode->Right();
    }

    // change the third expression to postfix
    exp3 = inToPostFix(exp3);
    // add third to ast
    addToAST(
        make_shared<Node>(currCstNode->Value(), Node::Type::ForExpression3),
        LeftChild);
    for (const auto &node : exp3) {
        addToAST(node, RightSibling);
    }

    return rootSubTreeNode;
}

NodePtr ASTParser::parsePrintF(NodePtr &currCstNode) {
    NodePtr rootSubTreeNode = currCstNode;
    currCstNode = currCstNode->Right(); // skip first '('

    while (currCstNode->value.value() != ")") {
        if (currCstNode->value.value() != ",") {
            auto nodeCopy =
                make_shared<Node>(currCstNode->Value(), Node::Type::OTHER);
            addToAST(nodeCopy, RightSibling);
        }
        currCstNode = currCstNode->Right();
    }
    return currCstNode;
}

NodePtr ASTParser::parseIFsORWhiles(NodePtr &currCstNode) {
    // Store the line of nodes in this subtree as a vector
    // Pass it into the function and then add them all in the AST in that orde
    NodePtr rootSubTreeNode = currCstNode;
    std::vector<NodePtr> assignmentNodes;

    while (currCstNode->Right() != nullptr) {
        assignmentNodes.push_back(currCstNode);
        currCstNode = currCstNode->Right();
    }
    assignmentNodes.push_back(currCstNode); // add the last ')' to vector

    //  Must parse the entire line in postFix notations
    assignmentNodes = inToPostFix(assignmentNodes);

    // Now for the size of the vector, add to the tree
    for (const auto &node : assignmentNodes) {
        addToAST(node, RightSibling);
    }
    return rootSubTreeNode;
}

NodePtr ASTParser::parseAssignment(NodePtr &currCstNode) {
    // Store the line of nodes in this subtree as a vector
    // Pass it into the function and then add them all in the AST in that orde
    NodePtr rootSubTreeNode = currCstNode;
    std::vector<NodePtr> assignmentNodes;

    while (currCstNode->Value().type() != Token::Type::Semicolon) {
        assignmentNodes.push_back(currCstNode);
        currCstNode = currCstNode->Right();
    }

    //  Must parse the entire line in postFix notations
    assignmentNodes = inToPostFix(assignmentNodes);

    // Now for the size of the vector, add to the tree
    for (const auto &node : assignmentNodes) {
        addToAST(node, RightSibling);
    }
    return rootSubTreeNode;
}

void ASTParser::addToAST(NodePtr node, InsertionMode mode) {

    node->leftChild = nullptr;
    node->rightSibling = nullptr;
    if (!root) {
        root = node;
    } else {
        if (mode == LeftChild) {
            lastASTNode->leftChild = node;

        } else {
            lastASTNode->rightSibling = node;
        }
    }
    lastASTNode = node;
}

Node::Type ASTParser::determineSemanticNodeType(const std::string &value) {
    if (value == "function" || value == "procedure" || isDataType(value) ){
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

std::vector<NodePtr> ASTParser::inToPostFix(const std::vector<NodePtr> &inFix) {
    vector<NodePtr> stack;
    vector<NodePtr> postFix;

    for (int i = 0; i < inFix.size(); ++i) {
        Token::Type tokType = inFix[i]->Value().type();

        if (tokType == Token::Type::Integer ||
            tokType == Token::Type::Identifier ||
            tokType == Token::Type::BooleanTrue ||
            tokType == Token::Type::BooleanFalse ||
            tokType == Token::Type::SingleQuotedString ||
            tokType == Token::Type::DoubleQuotedString) {
            postFix.push_back(inFix[i]); // display token
        } else {
            if (tokType == Token::Type::LParen) {
                stack.push_back(inFix[i]); // put on stack
            } else {
                if (tokType == Token::Type::RParen) {
                    bool finished = false;
                    while (!finished) {
                        if (stack.back()->value.type() == Token::Type::LParen) {
                            stack.pop_back();
                            finished = true;
                        } else {
                            postFix.push_back(
                                stack.back()); // display token at top of stack
                            stack.pop_back();
                        }
                    }
                    // INSERTING BRACKET CHECKS
                } else if (tokType == Token::Type::LBracket) {
                    postFix.push_back(inFix[i]); // display it and
                    stack.push_back(inFix[i]);   // put on stack
                } else if (tokType == Token::Type::RBracket) {
                    bool finished = false;
                    while (!finished) {
                        if (stack.back()->value.type() ==
                            Token::Type::LBracket) {
                            stack.pop_back();
                            finished = true;
                        } else {
                            postFix.push_back(
                                stack.back()); // display token at top of stack
                            stack.pop_back();
                        }
                    }
                    postFix.push_back(inFix[i]); // display the right bracket
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
                            if (stack.back()->value.type() ==
                                Token::Type::LParen) {
                                stack.push_back(inFix[i]); // put on stack
                            } else {
                                if (tokType == Token::Type::BooleanNot) {
                                    bool finished = false;
                                    while (!finished) {
                                        if (!stack.empty()) {
                                            if (stack.back()->value.type() ==
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
                                                if (stack.back()
                                                            ->value.type() ==
                                                        Token::Type::
                                                            BooleanNot ||
                                                    stack.back()
                                                            ->value.type() ==
                                                        Token::Type::Asterisk ||
                                                    stack.back()
                                                            ->value.type() ==
                                                        Token::Type::Slash ||
                                                    stack.back()
                                                            ->value.type() ==
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
                                                                ->value
                                                                .type() ==
                                                            Token::Type::
                                                                BooleanNot ||
                                                        stack.back()
                                                                ->value
                                                                .type() ==
                                                            Token::Type::
                                                                Asterisk ||
                                                        stack.back()
                                                                ->value
                                                                .type() ==
                                                            Token::Type::
                                                                Slash ||
                                                        stack.back()
                                                                ->value
                                                                .type() ==
                                                            Token::Type::
                                                                Modulo ||
                                                        stack.back()
                                                                ->value
                                                                .type() ==
                                                            Token::Type::Plus ||
                                                        stack.back()
                                                                ->value
                                                                .type() ==
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
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanNot ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Asterisk ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Slash ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Modulo ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Plus ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Minus ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanEqual ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanNotEqual ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Lt ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    Gt ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    LtEqual ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    GtEqual ||
                                                            stack.back()
                                                                    ->value
                                                                    .type() ==
                                                                Token::Type::
                                                                    BooleanAnd ||
                                                            stack.back()
                                                                    ->value
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
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanNot ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Asterisk ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Slash ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Modulo ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Plus ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Minus ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanEqual ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanNotEqual ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Lt ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        Gt ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        LtEqual ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        GtEqual ||
                                                                stack.back()
                                                                        ->value
                                                                        .type() ==
                                                                    Token::Type::
                                                                        BooleanAnd ||
                                                                stack.back()
                                                                        ->value
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