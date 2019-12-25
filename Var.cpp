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

Var::Var(const Var &v) : Var(v.value, v.sim, v.direction) {

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
    this->newValue = true;
}

double Var::calculate() {
    return this->value;
}

bool Var::hasNewValue() const {
    return this->newValue;
}

void Var::valueUsed() {
    this->newValue = false;
}


