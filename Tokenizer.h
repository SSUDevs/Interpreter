#ifndef ASSIGNMENT1_460_TOKENIZER_H
#define ASSIGNMENT1_460_TOKENIZER_H
#include <iostream>
#include <fstream>

using namespace std;

class Tokenizer
{
public:
    Tokenizer();

    void TokenizeFile();

private:
    string inputFileName;
    ifstream inputStream;
};

#endif // ASSIGNMENT1_460_TOKENIZER_H
