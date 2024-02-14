# Comment Remover for a C-like programming language:

This program is designed to identify and remove comments from input test files. 

It leverages a procedurally-driven deterministic finite state automaton (DFA) to accurately identify comments within the code.

## Objective

This is a preliminary step in preperation for building an interpreter for a C-like language in Backus-Naur Form. 

## How It Works

The program reads an input file, identifies comments (Both line and block) using a deterministic finite state automaton,
and removes these comments and outputs the cleaned code.

## Code Structure

The project currently utilizes two main components:

- `main.cpp`: The entry point of the program, which opens the input file, checks for errors, and initiates the comment removal process.
- `fileAsArray.h` and `fileAsArray.cpp`: Defines the `fileAsArray` class that contains the logic for reading the file, identifying, and removing comments based on the DFA.

## Contributors

- [Oasiss999](https://github.com/Oasiss999)
- [harrisb002](https://github.com/harrisb002)
- [EvanW2k](https://github.com/EvanW2k)
- [Zeroxa](https://github.com/Zeroxa)
