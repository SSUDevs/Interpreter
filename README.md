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

#### Objective

This initial step aims to prepare the source code for further processing by removing comments. It's essential for simplifying the code analysis in subsequent stages.

#### How It Works

- The program uses a deterministic finite state automaton (DFA) to identify and eliminate both line and block comments from the source code.
- The cleaned code is then outputted, ready for tokenization.

#### Code Structure

- `main.cpp`: Initiates the comment removal process.
- `fileAsArray.h` and `fileAsArray.cpp`: Implements the `fileAsArray` class for reading and processing the file according to DFA rules.

### 🚧 Tokenizing (In Progress)

The tokenizing stage is designed to convert the cleaned source code into a series of tokens. These tokens are used by the parser to understand the code's structure and semantics.

- **Current Status**: Implementation underway. This step involves using a DFA to identify tokens accurately.

### 🔲 Recursive Decent Parser

*Not yet implemented.*

### 🔲 Symbol Table

*Not yet implemented.*

### 🔲 Abstract Syntax Tree

*Not yet implemented.*

## Future Work

Moving forward, the project will focus on:

- **Finalizing Tokenization**: Completing the implementation to ensure accurate conversion of source code into tokens.
- **Recursive Decent Parsing**: Developing a parser to analyze the tokenized code's structure.
- **Symbol Table**: Implementing a symbol table for managing variable and function declarations.
- **Abstract Syntax Tree**: Constructing an AST to represent the program's structure for efficient execution.

The completion of these stages will culminate in a fully functional interpreter for a C-like language, enabling the execution of C-like programs with high efficiency and accuracy.


## Contributors

- [Oasiss999](https://github.com/Oasiss999)
- [harrisb002](https://github.com/harrisb002)
- [EvanW2k](https://github.com/EvanW2k)
- [Zeroxa](https://github.com/Zeroxa)
