cmake_minimum_required(VERSION 3.24)
project(Interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Interpreter main.cpp
        Token.cpp
        Token.h
        Tokenizer.cpp
        Tokenizer.h
        fileAsArray.h
        fileAsArray.cpp
        Node.cpp
        Node.h
        ConcreteSyntaxTree.cpp
        ConcreteSyntaxTree.h
        OutPutGenerator.cpp
        OutPutGenerator.h
        OutPutGenerator.cpp)
