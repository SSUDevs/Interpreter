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
       // cout<<currCstNode->value.value()<<endl;
        // Determine the semantic type and set it while creating root node
        Node::Type type = determineSemanticNodeType(cstNodeValue);
        // Create a new node with the same value and updated "type"
        auto newNode = make_shared<Node>(currCstNode->Value(), type);

        // Add as child or sibling based on the type
        if (type != Node::Type::OTHER) {
            addToAST(newNode, LeftChild);
            if( type == Node::Type::IF || type == Node::Type::WHILE){
                //parse if statements
                parseIFsORWhiles(currCstNode);
            }
            //cout<<newNode->value.value()<<endl;

        } else if (currCstNode->Value().type() == Token::Type::Identifier) {
            // Must be an assignment op

            parseAssignment(currCstNode);
            //cout<<currCstNode->value.value()<<endl;
        }

        // Move to the next important node
        while (currCstNode->Right() != nullptr) {
            currCstNode = currCstNode->Right();
            //cout<<currCstNode->value.value()<<endl;
        }

        // Drop into the important node of the CST
        currCstNode = currCstNode->Left();
    }
    return root;
}


NodePtr ASTParser::parseIFsORWhiles(NodePtr& currCstNode) {
    // Store the line of nodes in this subtree as a vector
    // Pass it into the function and then add them all in the AST in that orde
    NodePtr rootSubTreeNode = currCstNode;
    std::vector<NodePtr> assignmentNodes;

    currCstNode = currCstNode->Right();//skipping first '('
    while (currCstNode->value.value() !=")") {
        //cout<<currCstNode->value.value()<<endl;
        assignmentNodes.push_back(currCstNode);
        currCstNode = currCstNode->Right();

    }

    //cout<<currCstNode->value.value()<<endl;
    // Must parse the entire line in postFix notations
    assignmentNodes = inToPostFix(assignmentNodes);

    // Now for the size of the vector, add to the tree
    for (const auto &node : assignmentNodes) {
        //cout<<node->value.value()<<endl;
        addToAST(node, RightSibling);
    }
    //cout<<currCstNode->value.value()<<endl;
    return rootSubTreeNode;
}

NodePtr ASTParser::parseAssignment(NodePtr& currCstNode) {
    // Store the line of nodes in this subtree as a vector
    // Pass it into the function and then add them all in the AST in that orde
    NodePtr rootSubTreeNode = currCstNode;
    std::vector<NodePtr> assignmentNodes;

    while (currCstNode->Right() != nullptr) {
        //cout<<currCstNode->value.value()<<endl;
        assignmentNodes.push_back(currCstNode);
        currCstNode = currCstNode->Right();

    }

    //cout<<currCstNode->value.value()<<endl;
    // Must parse the entire line in postFix notations
    assignmentNodes = inToPostFix(assignmentNodes);

    // Now for the size of the vector, add to the tree
    for (const auto &node : assignmentNodes) {
       //cout<<node->value.value()<<endl;
        addToAST(node, RightSibling);
    }
    //cout<<currCstNode->value.value()<<endl;
    return rootSubTreeNode;
}

NodePtr ASTParser::getNextCSTNode() {
    return currCstNode ? (currCstNode->Right() ? currCstNode->Right()
                                               : currCstNode->Left())
                       : nullptr;
}

void ASTParser::addToAST(NodePtr node, InsertionMode mode) {
    //cout<<node->value.value()<<endl;
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
    if (value == "function" || value == "procedure" || isDataType(value) || value == "bool" || value == "int" ||value == "char") {
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
            tokType == Token::Type::SingleQuotedString ||
            tokType == Token::Type::DoubleQuotedString ) {
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
                } else if (tokType == Token::Type::LBracket){
                    postFix.push_back(inFix[i]); // display it and
                    stack.push_back(inFix[i]); // put on stack
                } else if (tokType == Token::Type::RBracket) {
                    bool finished = false;
                    while (!finished) {
                        if (stack.back()->value.type() == Token::Type::LBracket) {
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
                                                if (stack.back()->value.type() ==
                                                        Token::Type::
                                                            BooleanNot ||
                                                    stack.back()->value.type() ==
                                                        Token::Type::Asterisk ||
                                                    stack.back()->value.type() ==
                                                        Token::Type::Slash ||
                                                    stack.back()->value.type() ==
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
                                                                ->value.type() ==
                                                            Token::Type::
                                                                BooleanNot ||
                                                        stack.back()
                                                                ->value.type() ==
                                                            Token::Type::
                                                                Asterisk ||
                                                        stack.back()
                                                                ->value.type() ==
                                                            Token::Type::
                                                                Slash ||
                                                        stack.back()
                                                                ->value.type() ==
                                                            Token::Type::
                                                                Modulo ||
                                                        stack.back()
                                                                ->value.type() ==
                                                            Token::Type::Plus ||
                                                        stack.back()
                                                                ->value.type() ==
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