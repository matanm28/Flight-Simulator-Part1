//
// Created by matan on 12/17/19.
//

#include "Var.h"

Var::Var(int value, const string &sim, const string &direction) {
    this->value = value;
    this->sim = sim;
    this->direction = direction;
}

Var::Var(const string &sim, const string &direction) : Var(DEFAULT_VALUE, sim, direction) {}

int Var::getValue() const {
    return this->value;
}

const string &Var::getSim() const {
    return this->sim;
}

const string &Var::getDirection() const {
    return this->direction;
}


