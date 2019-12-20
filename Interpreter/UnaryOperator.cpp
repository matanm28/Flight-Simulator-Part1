//
// Created by matan on 05/11/2019.
//

#include "UnaryOperator.h"

UnaryOperator::UnaryOperator(Expression *exp) {
    this->exp = exp;
}

Expression *UnaryOperator::getExp() {
    return this->exp;
}

UnaryOperator::~UnaryOperator() {
    delete this->exp;
}







