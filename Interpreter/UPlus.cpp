//
// Created by matan on 05/11/2019.
//

#include "UPlus.h"

UPlus::UPlus(Expression *exp) : UnaryOperator(exp) {}

double UPlus::calculate() {
    return this->getExp()->calculate();
}


