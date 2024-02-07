//
// Created by Luis carmona on 2/7/24.
//

#include "Token.h"

Token::Token():_isAsterisk{false},_isSlash{false} {

}

bool &Token::isSlash() {
    return _isSlash;
}

bool &Token::isAsterisk() {
    return _isAsterisk;
}

void Token::print() {

    if(isAsterisk()){
        cout<<'*'<<endl;
    }
    if(isSlash()){
        cout<<'/'<<endl;
    }

}



