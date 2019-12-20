//
// Created by matan on 05/11/2019.
//

#include "BinaryOperator.h"

BinaryOperator::BinaryOperator(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}


Expression *BinaryOperator::getRight() {
    return this->right;
}

Expression *BinaryOperator::getLeft() {
    return this->left;
}

BinaryOperator::~BinaryOperator() {
    delete this->right;
    delete this->left;
}
