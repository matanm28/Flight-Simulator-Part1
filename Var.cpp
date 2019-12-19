//
// Created by matan on 12/17/19.
//

#include "Var.h"

Var::Var(float value, const string &sim, const string &direction) {
    this->value = value;
    this->sim = sim;
    this->direction = direction;
}

Var::Var(const string &sim, const string &direction) : Var(DEFAULT_VALUE, sim, direction) {}

Var::Var(const Var &v) {
    this->value = v.getValue();
    this->sim = v.getSim();
    this->direction = v.getDirection();
}

Var::Var(float value) : Var(value, "", "=") {}

float Var::getValue() const {
    return this->value;
}

const string &Var::getSim() const {
    return this->sim;
}

const string &Var::getDirection() const {
    return this->direction;
}

void Var::setValue(float value) {
    Var::value = value;
}


