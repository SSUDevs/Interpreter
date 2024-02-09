//
// Created by Luis carmona on 2/7/24.
//

#ifndef ASSIGNMENT1_460_TOKEN_H
#define ASSIGNMENT1_460_TOKEN_H
#include <iostream>

using namespace std;
class Token {

public:
    Token();
    bool &isSlash();
    bool &isAsterisk();
    void print();



private:
    bool _isSlash,_isAsterisk;

};


#endif //ASSIGNMENT1_460_TOKEN_H
int state =0;


