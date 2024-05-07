//
// Created by Evan on 4/24/2024.
//
#include "Interpreter.h"
#include "../ErrorHandler/ErrorHandler.h"
#include <cmath>

// Define a DEBUG flag
#define DEBUG false
// Define custom debug macro
#if DEBUG
#define debug std::cout
#else
#define debug 0 && std::cout
#endif

Interpreter::Interpreter(const NodePtr &astRoot, const SymTblPtr &symTblRoot) {
    // rootTable = symTblRoot;
    this->rootTable = symTblRoot;
    this->astRoot = astRoot;
    scopeStack.push(0);

    // locate main in AST
    this->PC = findFunctOrProcStart("main");
    debug << "MAIN FOUND AT LINE NUM: " << this->PC->Value().lineNum() << endl;

    PC = peekNext(PC);
    // start execution of program

    while (PC != nullptr) {
        debug << "START with value of: " << PC->Value().value()
             << " and line number: " << PC->Value().lineNum() << endl
             << endl;

        iteratePC();
    }

    debug << "Finished Execution" << endl;
}

void Interpreter::executeDeclaration(string variable) {
    SymTblPtr currTable = rootTable;
    while (currTable->GetName() != variable) {
        currTable = currTable->GetNextTable();
        if (currTable == nullptr) {
            throw std::runtime_error("No Symbol Table for " + variable);
        }
    }
    currTable->setDeclared(true);

    // if an array set value to an array of the declared size
    if (currTable->isArray()) {
        currTable->setValueSize(currTable->GetArraySize());
    } else {
        currTable->setValueSize(1);
    }
}

NodePtr Interpreter::iteratePC() {
    debug << "Iterator " << PC->Value().value() << " " << PC->Value().lineNum()
         << endl;
    debug << "Type " << PC->semanticTypeToString(PC->getSemanticType()) << endl;

    if (PC->getSemanticType() == Node::Type::END_BLOCK &&
        PC->Left() == nullptr) {
        debug << "! Within iterate PC and if block with PC value of: "
             << PC->Value().value()
             << " and line number : " << PC->Value().lineNum() << endl;
        debug << "!!! Semantic type is: "
             << PC->semanticTypeToString(PC->getSemanticType()) << endl;

        PC = nullptr;
        return PC;
    }

    if (!PC) {
        debug << "NullPTR" << endl;
        return nullptr;
    }

    // Handling different types of nodes
    switch (PC->getSemanticType()) {
    case Node::Type::BEGIN_BLOCK:
        break;
    case Node::Type::END_BLOCK: // return to last PC in stack
        debug << endl
             << endl
             << "!!!!!! STACK !!!!!!The PC tack is currently: "
             << pc_stack.top() << endl
             << endl;
        if (!pc_stack.empty()) {
            PC = pc_stack.top();
            pc_stack.pop();
            debug << "Returning to previous block, current PC restored to "
                 << PC->Value().value() << endl;
        } else {
            debug << "No more blocks to return to, finishing execution." << endl;
            PC = nullptr; // Make sure to set PC to nullptr to stop the program
            return nullptr;
        }
        break;
    case Node::Type::DECLARATION:
        debug << endl << endl << "Within DECLARATION case" << endl << endl;
        executeDeclaration(PC->Value().value());
        debug << endl << endl << "Out of the DECLARATION case" << endl << endl;
        if (!PC)
            return nullptr;

        break;
    case Node::Type::ASSIGNMENT:
        // Execute an assignment statements
        debug << endl << endl << "Within ASSIGNMENT case" << endl << endl;
        executeAssignment(PC);
        debug << "Out of the ASSIGNMENT case" << endl << endl;
        if (!PC)
            return nullptr;

        break;
    case Node::Type::IF: // also handles else
        debug << endl << endl << "Within IF case" << endl << endl;
        executeIF();
        debug << endl << endl << "Out of the IF case" << endl << endl;
        if (!PC)
            return nullptr;

        break;
    case Node::Type::FOR:
        debug << endl << endl << "Within FOR case" << endl << endl;
        executeFor();
        debug << endl << endl << "Out of the FOR case" << endl << endl;
        if (!PC)
            return nullptr;

        break;
    case Node::Type::WHILE:
        debug << endl << endl << "Within WHILE case" << endl << endl;

        executeWhile();
        debug << endl << endl << "Out of the WHILE case" << endl << endl;
        if (!PC)
            return nullptr;

        break;
    case Node::Type::PRINTF:
        debug << endl << endl << "Within PRINTF case" << endl << endl;
        executePrintF(PC);
        debug << endl << endl << "Out of PRINTF case" << endl << endl;
        if (!PC)
            return nullptr;

        break;
    case Node::Type::RETURN:
        debug << endl << endl << "Within RETURN case" << endl << endl;
        executeReturn();
        debug << endl << endl << "Out of the RETURN case" << endl << endl;

        scopeStack.pop();
        if (!PC)
            return nullptr;

        break;
    default:
        break;
    }

    if (PC->getSemanticType() == Node::Type::END_BLOCK &&
        PC->Left() == nullptr) {
        debug << "! Within iterate PC and if block with PC value of: "
             << PC->Value().value()
             << " and line number : " << PC->Value().lineNum() << endl;
        debug << "! Semantic type is: "
             << PC->semanticTypeToString(PC->getSemanticType()) << endl;

        PC = nullptr;
        return PC;
    }
    debug << endl
         << "After Case and within iteratePC with PC value of: "
         << PC->Value().value()
         << " and line number : " << PC->Value().lineNum() << endl;
    debug << "Semantic type is: "
         << PC->semanticTypeToString(PC->getSemanticType()) << endl;

    if (PC != nullptr) {
        NodePtr nextNode = PC->Right() ? PC->Right() : PC->Left();
        if (nextNode != nullptr) {
            PC = nextNode;
            debug << "Moved PC, now at: " << PC->Value().value()
                 << ", Line Number: " << PC->Value().lineNum() << endl;
        } else {
            debug << "No further nodes to process, ending." << endl;
            PC = nullptr;
        }
    }

    return PC;
}

NodePtr Interpreter::peekNext(NodePtr node) {
    if (!node)
        return nullptr;

    return node->Right() ? node->Right() : node->Left();
}

int Interpreter::findNumParamsOfFunctOrProc(const string name) {
    SymTblPtr currTable = rootTable;
    int count = 0;
    while (currTable) {

        if (currTable->GetIdType() == SymbolTable::IDType::parameterList) {
            if (currTable->procOrFuncName() == name) {
                count++;
            }
        }
        currTable = currTable->GetNextTable();
    }

    return count;
}

SymTblPtr Interpreter::getNthParamOfFuntOrProc(const string name, int num) {
    SymTblPtr currTable = rootTable;
    int count = 0;

    while (currTable) {
        if (currTable->GetIdType() == SymbolTable::IDType::parameterList) {
            if (currTable->procOrFuncName() == name) {
                count++;
                if (count == num)
                    return currTable;
            }
        }
        currTable = currTable->GetNextTable();
    }

    _globalErrorHandler.handle(37, PC->Value().lineNum());
    return nullptr;
}

void Interpreter::executeAssignment(NodePtr node) {
    debug << endl << endl << "GOING WITHIN executeAssignment" << endl;
    debug << "Node value of: " << node->Value().value()
         << " and line number : " << node->Value().lineNum() << endl;

    bool stringMode = false;
    auto variableName = node->Value().value();

    SymTblPtr table = getSymbolTable(node->Value().value());

    if (table->isArray() && table->GetDataType() == "char")
        stringMode = true;

    NodePtr nextNode = node->Right()->Right();

    // handle string assignment manually
    if (stringMode) {
        if (nextNode->Value().type() != Token::Type::DoubleQuotedString &&
            nextNode->Value().type() != Token::Type::SingleQuotedString)
            _globalErrorHandler.handle(35, nextNode->Value().lineNum());

        // update symbol table and ignore quotes
        for (int i = 1; i < nextNode->Value().value().size() - 1; ++i) {
            if (nextNode->Value().value().at(i) == '\\') {
                i++;
                if (nextNode->Value().value().at(i) == 'x') {
                    i++;
                    if (nextNode->Value().value().at(i) == '0') {
                        break;
                    }
                }
            }

            updateSymbolTable(variableName, nextNode->Value().value().at(i),
                              i - 1);
        }

    } else {

        NodePtr expression = node;

        if (node->getSemanticType() == Node::Type::ASSIGNMENT)
            expression = node->Right();

        debug << "Now calling evaluateExpression with root for expression "
             << expression->Value().value()
             << " and line number : " << PC->Value().lineNum() << endl;
        int result = evaluateExpression(expression, nullptr, true);
        debug << "Updating symbol table for variableName: " << variableName
             << " and result:  " << result << endl
             << endl;
        updateSymbolTable(variableName, result);
    }
}

// Applying the Add/Sub operators based on Token Type
int Interpreter::applyOperator(Token::Type op, int left, int right,
                               bool inAssignment /*default false*/) {
    switch (op) {
    case Token::Type::Plus:
        return left + right;
    case Token::Type::Minus:
        return left - right;
    case Token::Type::Asterisk:
        return left * right;
    case Token::Type::Slash:
        return left / right;
    case Token::Type::Modulo:
        return left % right;
    case Token::Type::Caret:
        return pow(left, right);
    case Token::Type::BooleanAnd:
        return left && right;
    case Token::Type::BooleanOr:
        return left || right;
    case Token::Type::BooleanEqual:
        return left == right;
    case Token::Type::BooleanNotEqual:
        return left != right;
    case Token::Type::Lt:
        return left < right;
    case Token::Type::Gt:
        return left > right;
    case Token::Type::LtEqual:
        return left <= right;
    case Token::Type::GtEqual:
        return left >= right;
    case Token::Type::AssignmentOperator:
        if (!inAssignment) {
            _globalErrorHandler.handle(33, PC->Value().lineNum());
        }
        // just return the right side of the equals, then evalExp will return it
        // too
        return right;

    default:
        throw std::runtime_error("Unsupported operator");
    }
}

int Interpreter::evaluateExpression(
    NodePtr exprRoot, const NodePtr endCase /*default is nullptr*/,
    const bool inAssignment /*default is false*/) {

    debug << endl << endl << "GOING WITHIN evaluateExpression" << endl;

    // Current stack being evaluated
    stack<int> evalStack;

    // Use the root of the expression
    NodePtr currentNode = exprRoot;

    // add first identifier to stack separately in case of assignment
    // it will be added as 0, as evalExp doesn't handle actual assigning
    if (inAssignment) {
        if (currentNode->Value().type() != Token::Type::Identifier) {
            _globalErrorHandler.handle(34, currentNode->Value().lineNum());
        }
        if (currentNode->Right()->Value().type() == Token::Type::LBracket) {
            string id = currentNode->Value().value();

            // set current node to beginning of inside []
            currentNode = currentNode->Right()->Right();

            // skip to end bracket
            while (currentNode->Value().type() != Token::Type::RBracket) {
                currentNode = currentNode->Right();
            }

            // push array access
            evalStack.push(0);

            // start on next part of expression
            currentNode = currentNode->Right();
        } else {
            evalStack.push(0);
        }
    }

    while (currentNode != endCase) {
        debug << "Parsing"
             << " " << currentNode->Value().value() << endl;
        if (isOperand(currentNode->Value())) {
            if (currentNode->Value().type() == Token::Type::Identifier) {
                // handle array access cases
                if (currentNode->Right()->Value().type() ==
                    Token::Type::LBracket) {
                    string id = currentNode->Value().value();

                    // set current node to beginning of inside []
                    currentNode = currentNode->Right()->Right();

                    NodePtr temp = currentNode;

                    // skip to end bracket
                    while (currentNode->Value().type() !=
                           Token::Type::RBracket) {
                        currentNode = currentNode->Right();
                    }

                    int arrayIdx = evaluateExpression(temp, currentNode);

                    // push array access
                    evalStack.push(getSymbolTableValue(id, arrayIdx));

                    // start on next part of expression
                    currentNode = currentNode->Right();
                } else {
                    string id = currentNode->Value().value();
                    SymTblPtr table = getSymbolTable(id);

                    if (table->GetIdType() == SymbolTable::IDType::function) {

                        int numParams = findNumParamsOfFunctOrProc(id);

                        currentNode =
                            currentNode->Right(); // iterate to next node
                        // get args for params and set the values for the
                        // appropriate symbol tables
                        for (int i = 1; i <= numParams; ++i) {

                            SymTblPtr currParamTbl =
                                getNthParamOfFuntOrProc(id, i);

                            if (!currParamTbl->GetIsDeclared()) {
                                executeDeclaration(currParamTbl->GetName());
                            }

                            // set table value of param before call
                            if (currentNode->Value().type() ==
                                Token::Type::Identifier) {
                                SymTblPtr currArgTable = getSymbolTable(
                                    currentNode->Value().value());
                                int argIndex = 0;

                                if (currArgTable->isArray()) {
                                    if (currentNode->Right()->Value().type() !=
                                        Token::Type::LBracket) {
                                        _globalErrorHandler.handle(
                                            38, currentNode->Value().lineNum());
                                    }

                                    // save identifier
                                    NodePtr identifier = currentNode;
                                    // pass identifier
                                    currentNode = currentNode->Right();
                                    // pass [
                                    currentNode = currentNode->Right();

                                    if (currentNode->Value().type() ==
                                        Token::Type::Identifier) {
                                        argIndex = getSymbolTableValue(
                                            currentNode->Value().value());
                                    } else {
                                        argIndex =
                                            stoi(currentNode->Value().value());
                                    }

                                    // skip argIndex
                                    currentNode = currentNode->Right();

                                    updateSymbolTable(
                                        currParamTbl->GetName(),
                                        getSymbolTableValue(
                                            identifier->Value().value(),
                                            argIndex));

                                } else {
                                    updateSymbolTable(
                                        currParamTbl->GetName(),
                                        getSymbolTableValue(
                                            currentNode->Value().value(),
                                            argIndex));
                                }

                            } else {
                                updateSymbolTable(
                                    currParamTbl->GetName(),
                                    stoi(currentNode->Value().value()));
                            }

                            currentNode =
                                currentNode->Right(); // iterate to next node
                        }

                        // push current node on call stack
                        pc_stack.push(currentNode);
                        debug << endl << endl << endl << endl;
                        debug << "Pushing program counter to make function "
                                "call. Current node is: "
                             << currentNode->Value().value() << endl;
                        debug << "Current PC value is: " << PC->Value().value()
                             << endl;
                        // find begin block node of function
                        PC = findFunctOrProcStart(id);

                        // change scope
                        scopeStack.push(getSymbolTable(id)->GetScope());

                        // exec function
                        executeFunctionOrProcedureCall();
                        debug << "Finishing the executeFunctionOrProcedureCall: "
                             << endl
                             << endl;
                        if (!PC) {
                            debug << "PC is null return " << endl;
                            return evalStack.top();
                        }
                        currentNode = PC;
                    }
                    evalStack.push(getSymbolTableValue(id));
                }
            } else {
                // push token values, with true/false mapping
                if (currentNode->Value().type() == Token::Type::BooleanTrue) {
                    evalStack.push(1);
                } else if (currentNode->Value().type() ==
                           Token::Type::BooleanFalse) {
                    evalStack.push(0);
                } else if (currentNode->Value().type() ==
                               Token::Type::SingleQuotedString ||
                           currentNode->Value().type() ==
                               Token::Type::DoubleQuotedString) {
                    // check that is a single char (string of size 1 + quotes)
                    if (currentNode->Value().value().size() != 3)
                        _globalErrorHandler.handle(
                            36, currentNode->Value().lineNum());

                    int ascii = currentNode->Value().value()[1];
                    evalStack.push(ascii);
                } else {
                    evalStack.push(stoi(currentNode->Value().value()));
                }
            }

        } else {

            Token::Type op = currentNode->Value().type();

            if (op == Token::Type::BooleanNot) { // only unary case
                int operand = evalStack.top();
                evalStack.pop();
                evalStack.push(!operand);
            } else {
                // In postfix order first get right then left
                int right = evalStack.top();
                evalStack.pop();
                int left = evalStack.top();
                evalStack.pop();
                int result = applyOperator(op, left, right, inAssignment);
                evalStack.push(result);
            }
        }

        currentNode = currentNode->Right();
    }
    // Whats left on the stack is the result
    return evalStack.top();
}

// Determine if the node represents an operand
bool Interpreter::isOperand(Token t) {
    return !isOperator(t);
    // Just lookin for plus and minus right now for simplicty
}

bool Interpreter::isOperator(Token t) {
    if (t.type() == Token::Type::Plus || t.type() == Token::Type::Minus ||
        t.type() == Token::Type::Slash || t.type() == Token::Type::Asterisk ||
        t.type() == Token::Type::Modulo || t.type() == Token::Type::Caret ||
        t.type() == Token::Type::Lt || t.type() == Token::Type::Gt ||
        t.type() == Token::Type::LtEqual || t.type() == Token::Type::GtEqual ||
        t.type() == Token::Type::BooleanAnd ||
        t.type() == Token::Type::BooleanOr ||
        t.type() == Token::Type::BooleanNot ||
        t.type() == Token::Type::BooleanEqual ||
        t.type() == Token::Type::BooleanNotEqual ||
        t.type() == Token::Type::AssignmentOperator)
        return true;
    return false;
}

void Interpreter::executeIF() {

    debug << "EXECUTING IF" << endl;

    int bCount = 0;

    bool choseIf = false;

    PC = PC->Right();

    // evaluate expression
    int result = evaluateExpression(PC);

    if (result != 0) { // execute if block and skip the else (if it exists)
        debug << "Entering IF block" << endl;

        while (PC->getSemanticType() != Node::Type::BEGIN_BLOCK) {
            PC = peekNext(PC);
        }

        choseIf = true;
        while (PC->getSemanticType() != Node::Type::END_BLOCK) {
            iteratePC();
            if (!PC)
                return;
        }

        if (peekNext(PC)->getSemanticType() == Node::Type::ELSE) {
            debug << "Skipping ELSE block" << endl;

            PC = peekNext(PC); // skip end block

            debug << "skip else" << endl;
            // skip over else block
            while (bCount > 0 ||
                   PC->getSemanticType() != Node::Type::END_BLOCK) {
                PC = peekNext(PC);
                if (PC->getSemanticType() == Node::Type::BEGIN_BLOCK)
                    bCount++;
                if (PC->getSemanticType() == Node::Type::END_BLOCK)
                    bCount--;
            }

            // step past end block of else
        }

    } else { // skip if block and execute else block (if it exists)
        debug << "Skipping IF block, checking for ELSE" << endl;

        // skip over if block
        while (bCount > 0 || PC->getSemanticType() != Node::Type::END_BLOCK) {
            PC = peekNext(PC);
            if (PC->getSemanticType() == Node::Type::BEGIN_BLOCK)
                bCount++;
            if (PC->getSemanticType() == Node::Type::END_BLOCK)
                bCount--;
        }

        // look for else
        if (peekNext(PC)->getSemanticType() == Node::Type::ELSE) {
            // step past end block of if
            PC = peekNext(PC);

            debug << "entering else" << endl;
            while (PC->getSemanticType() != Node::Type::END_BLOCK) {
                iteratePC();
                if (!PC)
                    return;
            }
        }
    }

    debug << "exiting if" << endl;
    debug << endl
         << "The current PC value of: " << PC->Value().value()
         << " and line number : " << PC->Value().lineNum() << endl;
    if (PC)
        PC = peekNext(PC); // Move past the last END_BLOCK
}

int Interpreter::getSymbolTableValue(const string &name,
                                     int index /*default 0*/) {
    SymTblPtr currTable = rootTable;
    while (currTable->GetName() != name) {
        currTable = currTable->GetNextTable();
        if (currTable == nullptr) {
            throw std::runtime_error("No Symbol Table for " + name);
        }
    }

    return currTable->GetValue().at(index);
}

void Interpreter::updateSymbolTable(const string &name, int value,
                                    int index /*default 0*/) {
    // Needs logic to update the symbol table entry for 'name' with 'value'
    // Will be used in assignments
    SymTblPtr tempRoot = rootTable;

    if (UpdateTable(tempRoot, name, value, index)) {
        return;
    } else {
        debug << "failed to update symbol table value with name (" << name
             << ") to value (" << value << ")" << endl;
        exit(377);
    }
}

bool Interpreter::UpdateTable(SymTblPtr root, const string &name, int value,
                              int index) {
    if (root == nullptr) {
        return false;
    }
    if (root->GetName() == name) {
        root->setValue(value, index);
        return true;
    }
    return UpdateTable(root->GetNextTable(), name, value, index);
}

void Interpreter::executeFor() {

    debug << "Entering For" << endl;
    PC = peekNext(PC);

    // grab initial statement
    NodePtr initStmt = peekNext(PC); // skip to var name

    // skip to condition
    while (PC->Right()) {
        PC = PC->Right();
    }

    NodePtr condition = PC->Left()->Right();
    PC = condition;

    // skip to update statement
    while (PC->Right())
        PC = PC->Right();
    NodePtr updateStmt = PC->Left()->Right();

    // skip to body
    while (peekNext(PC)->getSemanticType() != Node::Type::BEGIN_BLOCK) {
        PC = peekNext(PC);
    }

    NodePtr body = peekNext(PC);

    executeAssignment(initStmt);

    while (evaluateExpression(condition)) {
        debug << "While evaluating expression in for loop" << endl
             << endl
             << endl;

        PC = body; // Proceed after the for-loop

        while (PC->getSemanticType() != Node::Type::END_BLOCK) {
            iteratePC();
            if (!PC)
                return;
        }

        executeAssignment(updateStmt);
    }

    // Move PC past the for loop
    PC = peekNext(PC);

    //debug << "Exiting For" << endl;
}

void Interpreter::executeWhile() {
    debug << endl << endl << "ENTERING WHILE LOOP" << endl;

    // grab initial statement
    NodePtr condition = peekNext(PC); // skip to var name
    debug << "condition is: " << condition->Value().value() << endl;
    PC = condition;

    // skip to body (FOR NOW JUST ONE STATEMENT IN WHILE)
    while (peekNext(PC)->getSemanticType() != Node::Type::BEGIN_BLOCK) {
        PC = peekNext(PC);
    }

    NodePtr body = peekNext(PC);

    while (evaluateExpression(condition)) {
        debug << "During evaluating expression in While loop" << endl
             << endl
             << endl;
        PC = body; // Proceed after while loop
        debug << "PC value for body is now: " << PC->Value().value() << endl;

        while (peekNext(PC)->getSemanticType() != Node::Type::END_BLOCK) {
            iteratePC();
            debug << endl << endl << "After IteratePC in While loop" << endl;
            debug << endl
                 << "PC value is: " << PC->Value().value()
                 << " and line number : " << PC->Value().lineNum() << endl;

            if (PC->getSemanticType() == Node::Type::END_BLOCK &&
                PC->Left() == nullptr) {
                debug << "! Within iterate PC and if block with PC value of: "
                     << PC->Value().value()
                     << " and line number : " << PC->Value().lineNum() << endl;
                debug << "!! Semantic type is: "
                     << PC->semanticTypeToString(PC->getSemanticType()) << endl;

                PC = nullptr;
                return;
            }
        }
    }
    debug << endl << endl << "After condition is false." << endl;
    debug << endl
         << "PC value is: " << PC->Value().value()
         << " and line number : " << PC->Value().lineNum() << endl;

    // Move PC past the for loop
    PC = peekNext(PC);

    debug << endl << endl << "EXITING WHILE LOOP" << endl;
}

void Interpreter::executePrintF(NodePtr Node) {
    debug << "Executing printf ..." << endl;
    // copy of original node
    NodePtr currNode = Node;

    // first node should be printf so the next one will contain the string
    currNode = currNode->Right();

    // obtain the string value from the node
    string printStatement = currNode->Value().value();

    // move the currnode to either a nullptr or first argument
    currNode = currNode->Right();

    vector<string> arguments;
    int arg_Index = 0;

    // go until the end of the printf statement

    while (currNode != nullptr) {

        // if the value is a string argument add the to the corresponding vector
        if (currNode->Value().type() == Token::Type::Identifier) {
            arguments.push_back(currNode->Value().value());
        }
        // if the value is a int argument add the to the corresponding vector

        currNode = currNode->Right();
    }

    // if both vectors are empty then no arguments were used so just print the
    // string and exit function
    if (arguments.empty()) {
        for (int i = 1; i < printStatement.size() - 1; ++i)
            cout << printStatement[i];
        cout << endl;

        while (PC->Right())
            PC = PC->Right();

        debug << "Done executing printf" << endl;

        return;
    }

    // we do have arguments passed so parse the print statement printing
    // character by character if we come across a % check the next character to
    // print the right argument if we see a \ then check for an n to add space
    // character
    for (int i = 0; i < printStatement.size(); i++) {
        if (printStatement.at(i) == '%') {
            i++;
            if (printStatement.at(i) == 'd') {
                cout << getSymbolTableValue(arguments.at(arg_Index));
                arg_Index++;
            } else if (printStatement.at(i) == 's') {
                SymTblPtr currTable = rootTable;
                while (currTable->GetName() != arguments.at(arg_Index)) {
                    currTable = currTable->GetNextTable();
                    if (currTable == nullptr) {
                        throw std::runtime_error("No Symbol Table for " +
                                                 arguments.at(arg_Index));
                    }
                }

                vector<int> astring = currTable->GetValue();
                for (int i = 0; i < astring.size(); i++) {
                    if (astring.at(i) == '\\') {
                        i++;
                        if (astring.at(i) == 'x') {
                            i++;
                            if (astring.at(i) == '0') {
                                break;
                            }
                        }
                    }
                    cout << astring.at(i);
                }
                arg_Index++;

            } else {
                exit(411);
            }

        } else if (printStatement.at(i) == '\\') {
            i++;
            if (printStatement.at(i) == 'n') {
                cout << " ";
            } else {
                exit(412);
            }

        } else {
            if (printStatement[i] != '"')
                cout << printStatement[i];
        }
    }
    debug << endl;

    debug << "Done executing printf" << endl;

    while (PC->Right())
        PC = PC->Right();

    return;
}

NodePtr Interpreter::findFunctOrProcStart(const string name) {
    debug << "Searching for function/procedure: " << name << endl;

    NodePtr currNode = astRoot;
    SymTblPtr currTable = rootTable;

    while (currNode) {
        if (currNode->getSemanticType() == Node::Type::DECLARATION) {
            // Get next symbol table for each declaration found in AST
            debug << "FOUND DECLARATION WITH NAME: " << currTable->GetName()
                 << endl;

            if (currTable->GetName() == name) {

                while (currNode->getSemanticType() != Node::Type::BEGIN_BLOCK) {
                    currNode = peekNext(currNode);
                }

                return currNode;
            }

            currTable = currTable->GetNextTable();

            // iterate past tables formed by params
            while (currTable->GetIdType() == SymbolTable::IDType::parameterList)
                currTable = currTable->GetNextTable();
        }
        currNode = peekNext(currNode);
    }
    throw std::runtime_error("Function or Procedure not found.");
}

SymTblPtr Interpreter::getSymbolTable(const std::string &name) {
    SymTblPtr currTable = rootTable;
    while (currTable->GetName() != name) {
        currTable = currTable->GetNextTable();
        if (currTable == nullptr) {
            throw std::runtime_error("No Symbol Table for " + name);
        }
    }

    return currTable;
}
SymTblPtr Interpreter::getSTofFuncOrProcByScope(const int scope) {
    SymTblPtr currTable = rootTable;
    while (currTable) {

        if (currTable->GetIdType() == SymbolTable::IDType::function ||
            currTable->GetIdType() == SymbolTable::IDType::procedure) {

            if (currTable->GetScope() == scope)
                return currTable;
        }

        currTable = currTable->GetNextTable();
        if (currTable == nullptr) {
            throw std::runtime_error("No funct or proc for scope " + scope);
        }
    }

    return currTable;
}

void Interpreter::executeFunctionOrProcedureCall() {
    debug << "Entering function/procedure call..." << endl;

    // Save curr scope for comparison
    int initialScope = scopeStack.top();

    // While in same scope (function has not returned)
    while (scopeStack.top() == initialScope) {
        debug << "Current PC before iterating: " << PC->Value().value()
             << ", Line: " << PC->Value().lineNum() << endl;
        iteratePC();
        if (!PC)
            break;
    }

    // After returning from function
    debug << "Exiting function/procedure call..." << endl;
    // Ensure PC is restored
    if (!pc_stack.empty()) {
        PC = pc_stack.top();
        pc_stack.pop();
        debug << "PC restored to: " << PC->Value().value()
             << ", Line: " << PC->Value().lineNum() << endl;
    }
}

void Interpreter::executeReturn() {
    debug << "Executing return" << endl;
    int retValue;

    if (PC->Right()->Value().type() == Token::Type::Identifier) {
        retValue = getSymbolTableValue(PC->Right()->Value().value());
    } else {
        retValue = stoi(PC->Right()->Value().value());
    }

    string tblID = getSTofFuncOrProcByScope(scopeStack.top())->GetName();

    // store return value in value of func/proc
    executeDeclaration(tblID);
    updateSymbolTable(tblID, retValue, 0);
}