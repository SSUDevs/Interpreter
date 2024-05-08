# C-like Language Interpreter Project

## Overview

The goal of this project is to build an interpreter for a C-like language by following a comprehensive development process. This process includes several critical stages, each contributing to the interpreter's capability to parse and execute C-like code efficiently.

The development stages are:

1. **Ignoring Comments**
2. **Tokenizing**
3. **Recursive Decent Parsing**
4. **Symbol Table Implementation**
5. **Abstract Syntax Tree Construction**

Each stage is designed to address a specific aspect of language interpretation, from preprocessing the source code to executing it.

## Implemented Features

### ✅ Comment Removal for a C-like Programming Language

This initial step aims to prepare the source code for further processing by removing comments. It's essential for simplifying the code analysis in subsequent stages. The program uses a deterministic finite state automaton (DFA) to identify and eliminate both line and block comments from the source code. The cleaned code is then outputted, ready for tokenization.

- `main.cpp`: Initiates the comment removal process.
- `fileAsArray.h` and `fileAsArray.cpp`: Implements the `fileAsArray` class for reading and processing the file according to DFA rules.

### ✅ Tokenizing

The tokenizing stage is designed to convert the cleaned source code into a series of tokens. These tokens are used by the parser to understand the code's structure and semantics.

- `Token.h` and `Token.cpp`: Defines all recognizable tokens used for tokenizing
- `Tokenizer.h` and `Tokenizer.cpp`: Creates tokens using a DFA to represent the codes structure and semantics

### ✅ Recursive Decent Parser

Creates a concrete syntax tree (CST) based upon the Backus-Naur Form (BNF) language definition using a procedurally-driven DFA. Utilizes an LCRS binary tree (Left-Child, Right-Sibling) to store the CST. The program may also display the resulting CST in breadth-first order, if desired.

- `Node.h` and `Node.cpp`: Used for the parser's internal representation. Each Node instance represents a part of the source code, such as a token or a syntax rule, and can link to child nodes and sibling nodes to form a tree structure.
- `Parser.h` and `Parser.cpp`:Implement the Parser class which takes a sequence of tokens as input and constructs the CST by recursively applying grammar rules defined in the BNF. The parser checks the source code's syntax and generates a parse tree that reflects the code's hierarchical structure.
- `ConcreteSyntaxTree.h` and `ConcreteSyntaxTree.cpp`: Provide functionalities to manage the Concrete Syntax Tree, allowing for the insertion and navigation of nodes within the tree. Used to represent the parsed source code in a hierarchical manner, allowing for further analysis or interpretation.
- `OutPutGenerator.h` and `OutPutGenerator.cpp`: Generate output based on the constructed syntax tree. Includes printing the tree structure in a breadth-first order for debugging or visualization purposes, as well as generating intermediate code or direct interpretation for execution.

### ✅ Symbol Table

Creates symbol tables for all the defined variables (including their type and scope) and the names of all functions and procedures to be used for semantic analysis, scope management, and identifier resolution in the parsing process.

- This includes:

  - Ensuring that variables and functions are declared and accessed within their respective scopes.
  - Associating identifiers with their data types and values, as well as checking for type consistency across operations.
  - Handling the declaration and invocation of functions and procedures, including parameter passing mechanisms.
  - Identifying undeclared identifiers, type mismatches, and scope violations.

- `SymbolTable.h` and `SymbolTable.cpp`: Define and implement the SymbolTable class, which represents individual entries in the symbol table. Each entry can denote a variable, function, procedure, or a parameter list, with attributes such as name, data type, identifier type, scope level, and array-related properties. The symbol table entries are used for checking variable declarations, resolving identifier references, and performing type checking during the interpretation process.
- `SymbolTablesLinkedList.h` and `SymbolTablesLinkedList.cpp`: Responsible for managing a linked list of SymbolTable entries, facilitating the construction and manipulation of the entire symbol table. This structure supports the nesting of scopes and the hierarchical nature defined in the BNF.

### ✅ Abstract Syntax Tree

- Creates an Abstract Syntax Tree (AST) based on the Concrete Syntax Tree (CST). 
- An Abstract Syntax Tree is not a clone of a Concrete Syntax Tree. 
- Utilizes an LCRS binary tree (Left-Child, Right-Sibling) to store the AST. 
- Allows for the isplay of the resulting AST in breadth-first order.

### ✅ Program Execution 

- Maintains a stack data structure and a program counter to keep track of the flow-of-control as your program interprets and executes an input program.
- Uses the symbol table to maintain variable values during program interpretation and execution.
- Traverses the Abstract Syntax Tree when executing statements.
- Starts at the first statement in the main procedure.
- The AST contains Boolean and numerical expressions in postfix notation to make it easy to evaluate the expressions during program interpretation and execution.
- Uses a stack data structure to evaluate the postfix notation expression.


# Browser code editor 

## Overview

This sandbox allows one to write and execute code in the browser utilizing an interpreter for a C-like language built by my colleagues and I as well as a variety of others through Pistin API

### Tools
- React + Vite
- Piston API [https://piston.readthedocs.io/en/latest/api-v2/#request](https://piston.readthedocs.io/en/latest/api-v2/#request)
- Monaco React Editor: [https://www.npmjs.com/package/@monaco...](https://www.npmjs.com/package/@monaco-editor/react)
- Chakra UI: [https://chakra-ui.com](https://chakra-ui.com/)


## Installation & Usage
Either one can
1. Clone the repository: `git clone <repository-url>`
2. In root directory:
  - Build: `./build.sh`
  - Start servers: `./start.sh`

Or visit Blue at: 

**Have Fun & let me know of any errors please!**

## Contributors

- [Oasiss999](https://github.com/Oasiss999)
- [harrisb002](https://github.com/harrisb002)
- [EvanW2k](https://github.com/EvanW2k)
- [Zeroxa](https://github.com/Zeroxa)



