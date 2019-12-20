//
// Created by matan on 05/11/2019.
//

#include "Minus.h"

double Minus::calculate() {
    return this->getLeft()->calculate() - this->getRight()->calculate();
}

Minus::Minus(Expression *left, Expression *right) : BinaryOperator(left, right) {}
