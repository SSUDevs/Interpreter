//
// Created by Evan on 4/24/2024.
//
#include "Interpreter.h"

Interpreter::Interpreter(const NodePtr &astRoot, const SymTblPtr &symTblRoot) {
    // rootTable = symTblRoot;
    this->rootTable = symTblRoot;
    this->astRoot = astRoot;

    // locate main in AST
    this->PC = findMain(astRoot, rootTable);
    cout << "MAIN FOUND: " << endl
         << "PC LineNum: " << this->PC->Value().lineNum() << endl;
}

// Traverse AST until DECLARATION is found then look in Symbol table that
// IDENTIFIER_NAME == "main" from token value
NodePtr Interpreter::findMain(const NodePtr &astroot,
                              const SymTblPtr &symroot) {
    NodePtr currAst = astroot;
    SymTblPtr currTable = symroot;

    while (currAst) {
        cout << "CURRENT NODE VALUE: " << currAst->Value().value() << endl;
        cout << "CURRENT NODE TYPE: "
             << currAst->semanticTypeToString(currAst->getSemanticType())
             << endl;
        if (currAst->getSemanticType() == Node::Type::DECLARATION) {
            // Get next symbol table for each declaration found in AST
            currTable = currTable->GetNextTable();
            cout << "FOUND DECLARATION WITH NAME: " << currTable->GetName()
                 << endl;

            if (currTable->GetName() == "main") {
                return currAst;
            }
        }
        currAst = currAst->Right() ? currAst->Right() : currAst->Left();
    }
    throw std::runtime_error("Main function not found.");
}

NodePtr Interpreter::iteratePC() {

    if (!PC)
        return nullptr; // Safety check

    // Handling different types of nodes
    switch (PC->getSemanticType()) {
    case Node::Type::DECLARATION:
        // Handle declarations
        break;
    case Node::Type::ASSIGNMENT:
        // Execute an assignment statement
        executeAssignment(PC);
        break;
    case Node::Type::IF:
    case Node::Type::ELSE:
    case Node::Type::FOR:
    case Node::Type::WHILE:
        // Control flow handling
        // handleControlFlow(PC);
        break;
    default:
        break;
    }

    // Move to next node by default (override in control flow handling)
    PC = PC->Right() ? PC->Right() : PC->Left();

    return PC;
}

NodePtr Interpreter::peekNext() {
    if (!PC)
        return nullptr;

    // Peek without changing the PC
    return PC->Right() ? PC->Right() : PC->Left();
}

void Interpreter::executeAssignment(NodePtr node) {
    auto variableName = node->Left()->Value().value();
    auto expression = node->Right();
    int result = evaluateExpression(expression);
    updateSymbolTable(variableName, result);
}

// Applying the Add/Sub operators based on Token Type
int Interpreter::applyOperator(Token::Type op, int left, int right) {
    switch (op) {
    case Token::Type::Plus:
        return left + right;
    case Token::Type::Minus:
        return left - right;
    // Add other operators
    default:
        throw std::runtime_error("Unsupported operator");
    }
}

int Interpreter::evaluateExpression(NodePtr exprRoot) {
    // Current stack being evaluated
    stack<int> evalStack;

    // Use the root of the exporession
    NodePtr currentNode = exprRoot;

    while (currentNode) {
        if (isOperator(currentNode->Value())) {
            evalStack.push(stoi(currentNode->Value().value()));
        } else {
            // In postfix order first get right then left
            int right = evalStack.top();
            evalStack.pop();
            int left = evalStack.top();
            evalStack.pop();
            int result =
                applyOperator(currentNode->Value().type(), left, right);
            evalStack.push(result);
        }

        currentNode = currentNode->Right();
    }
    // Whats left on the stack is the result
    return evalStack.top();
}

// Determine if the node represents an operand
bool Interpreter::isOperand() {
    return isOperator(this->astRoot->Value());
    // Just lookin for plus and minus right now for simplicty
}

bool Interpreter::isOperator(Token t) {
    if (t.type() == Token::Type::Plus || t.type() == Token::Type::Minus)
        // || t.type() == Token::Type::Slash || t.type() ==
        // Token::Type::Asterisk || t.type() == Token::Type::Modulo || t.type()
        // == Token::Type::Caret || t.type() == Token::Type::Lt || t.type() ==
        // Token::Type::Gt || t.type() == Token::Type::LtEqual || t.type() ==
        // Token::Type::GtEqual || t.type() == Token::Type::BooleanAnd ||
        // t.type() == Token::Type::BooleanOr ||
        // t.type() == Token::Type::BooleanNot ||
        // t.type() == Token::Type::BooleanEqual ||
        // t.type() == Token::Type::BooleanNotEqual)
        return true;
    return false;
}

void Interpreter::updateSymbolTable(const string &name, int value) {
    // Needs logic to update the symbol table entry for 'name' with 'value'
    // Will be used in assignments
}
