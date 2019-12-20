//
// Created by matan on 05/11/2019.
//

#include "Plus.h"

double Plus::calculate() {
    return this->getLeft()->calculate() + this->getRight()->calculate();
}

Plus::Plus(Expression *left, Expression *right) : BinaryOperator(left, right) {}
