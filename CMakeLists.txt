cmake_minimum_required(VERSION 3.24)
project(Interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Interpreter
        src/main.cpp
        src/Token/Token.cpp
        src/Token/Token.h
        src/Token/Tokenizer.cpp
        src/Token/Tokenizer.h
        src/CommentRemoval/fileAsArray.h
        src/CommentRemoval/fileAsArray.cpp
        src/Node/Node.cpp
        src/Node/Node.h
        src/CST/ConcreteSyntaxTree.cpp
        src/CST/ConcreteSyntaxTree.h
        src/OutputGenerator/OutPutGenerator.cpp
        src/OutputGenerator/OutPutGenerator.h
        src/CST/Parser.cpp
        src/SymbolTable/SymbolTable.cpp
        src/SymbolTable/SymbolTable.h
        src/SymbolTable/SymbolTablesLinkedList.h
        src/SymbolTable/SymbolTablesLinkedList.cpp
        src/AST/AST.cpp
        src/AST/AST.h
        src/AST/AST.cpp
        src/AST/AST.h
        src/AST/ASTParser.cpp
        src/Interpreter/Interpreter.cpp
        src/ErrorHandler/ErrorHandler.cpp

)
