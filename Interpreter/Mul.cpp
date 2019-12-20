//
// Created by matan on 05/11/2019.
//

#include "Mul.h"

double Mul::calculate() {
    return this->getLeft()->calculate() * this->getRight()->calculate();
}

Mul::Mul(Expression *left, Expression *right) : BinaryOperator(left, right) {}
