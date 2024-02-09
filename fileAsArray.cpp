//
// Created by Luis carmona on 2/8/24.
//

#include "fileAsArray.h"



fileAsArray::fileAsArray(std::string fileName) {
    inputStream.open(fileName, std::ios::in);
    inputFileName= fileName;

}


void fileAsArray::readFile(){

    if( ! inputStream.is_open()) {
        std::cout<< "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout<< "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }
    
    char c;
    
    while (inputStream.get(c) && !inputStream.eof()){
        std::cout<<c;
        file.push_back(c);
    }

    inputStream.close();
    std::cout<<"Done reading File"<<std::endl;

}