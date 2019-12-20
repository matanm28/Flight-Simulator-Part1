//
// Created by matan on 05/11/2019.
//

#include "UMinus.h"

UMinus::UMinus(Expression *exp) : UnaryOperator(exp) {

}

double UMinus::calculate() {
    return -this->getExp()->calculate();
}


