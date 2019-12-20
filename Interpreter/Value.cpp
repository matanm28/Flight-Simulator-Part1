//
// Created by matan on 05/11/2019.
//
#include "Value.h"

Value::Value(double value) : Expression() {
    this->value = value;
}

double Value::calculate() {
    return this->value;
}

Value::~Value() {

}

