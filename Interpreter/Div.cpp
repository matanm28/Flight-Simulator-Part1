//
// Created by matan on 05/11/2019.
//

#include "Div.h"

double Div::calculate() {
    double a, b;
    a = this->getLeft()->calculate();
    b = this->getRight()->calculate();
    if (b == 0 && a != 0) {
        throw "division by zero";
    } else {
        return a / b;
    }
}


Div::Div(Expression *left, Expression *right) : BinaryOperator(left, right) {}
