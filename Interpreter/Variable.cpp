//
// Created by matan on 04/11/2019.
//
#include "Variable.h"

Variable::Variable(const string &name, double value) {
    this->name = name;
    this->value = value;
}

Variable::Variable(Variable &var) {
    this->name = var.name;
    this->value = var.value;

}

double Variable::calculate() {
    return this->value;
}


Variable &Variable::operator+(Expression &other) {
    this->value = this->value + other.calculate();
    return *this;
}

Variable &Variable::operator-(Expression &other) {
    this->value = this->value - other.calculate();
    return *this;
}

//prefix
Variable &Variable::operator++(int) {
    return ++*this;
    Variable *temp = new Variable(*this);
    ++*this;
    return *temp;
}

//prefix
Variable &Variable::operator--(int) {
    Variable *temp = new Variable(*this);
    --*this;
    return *temp;
}

//postfix
Variable &Variable::operator++() {
    this->value++;
    return *this;
}

//postfix
Variable &Variable::operator--() {
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double val) {
    this->value += val;
    return *this;
}

Variable &Variable::operator-=(double val) {
    this->value -= val;
    return *this;
}

bool Variable::operator==(const Variable &other) const {
    return (this->name == other.name && this->value == other.value);
}

bool Variable::operator!=(const Variable &other) const {
    return !(*this == other);
}

bool Variable::operator<(const Variable &other) const {
    return name < other.name;
}

bool Variable::operator>(const Variable &other) const {
    return other < *this;
}

bool Variable::operator<=(const Variable &other) const {
    return !(other < *this);
}

bool Variable::operator>=(const Variable &other) const {
    return !(*this < other);
}

const string &Variable::getName() const {
    return this->name;
}

double Variable::getValue() const {
    return this->value;
}

Variable::~Variable() {

}










