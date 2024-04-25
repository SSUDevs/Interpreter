//
// Created by Evan on 4/24/2024.
//
#include "Interpreter.h"

Interpreter::Interpreter(const NodePtr &astRoot, const SymTblPtr &symTblRoot) {
    rootTable = symTblRoot;


    // locate main in AST

}

NodePtr Interpreter::iteratePC() {

    NodePtr nextPC;

    // find nextPC in left child or right sibling of current


    PC = nextPC;

    return PC;
}

NodePtr Interpreter::peekNext() {

    NodePtr nextPC;

    return nextPC;
}