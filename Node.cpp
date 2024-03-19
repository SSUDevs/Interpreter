//
// Created by Luis carmona on 3/19/24.
//

#include "Node.h"

#include <utility>

Node::Node(Token  token):_token(std::move(token)) {

    _left= nullptr;
    _right = nullptr;

}

Token &Node::AToken() {
    return _token;
}

Node &Node::Right() {
    return *_right;
}

Node &Node::left() {
    return *_left;
}

Node::~Node() {

delete _left;
delete _right;
}

