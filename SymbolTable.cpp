//
// Created by sapir on 17/12/2019.
//

#include "SymbolTable.h"

SymbolTable *SymbolTable::unifiedSymbolTable = nullptr;

SymbolTable::SymbolTable() {
    //empty or not?
}

SymbolTable *SymbolTable::getSymbolTable() {
    if (!unifiedSymbolTable) {
        unifiedSymbolTable = new SymbolTable();
    }
    return unifiedSymbolTable;
}

void SymbolTable::addVar(string varName, string sim, string direction, float value) {
    Var *var = new Var(value, sim, direction);
    this->nameToVar.insert({varName, var});
    this->simToVar.insert({sim, var});
}

void SymbolTable::addVar(string varName, string sim, string direction) {
    this->addVar(varName, sim, direction, DEFAULT_VALUE);
}

void SymbolTable::addVar(string varName, float value) {
    Var *var = new Var(value);
    this->nameToVar.insert({varName, var});
}

//todo: maybe delete?
void SymbolTable::addVar(string varName, Var *var) {
    this->nameToVar.insert({varName, var});
    this->simToVar.insert({var->getSim(), var});
}


void SymbolTable::setVarByName(string varName, float value) {
    this->mutexLock.lock();
    this->nameToVar.find(varName)->second->setValue(value);
    this->mutexLock.unlock();
}

void SymbolTable::setVarBySim(string sim, float value) {
    this->mutexLock.lock();
    this->simToVar.find(sim)->second->setValue(value);
    this->mutexLock.unlock();
}


Var SymbolTable::getVar(string varName) {
    if (this->nameToVar.find(varName) != this->nameToVar.cend()) {
        return *this->nameToVar.find(varName)->second;
    } else {
        return NULL;
    }
}

string SymbolTable::varExists(string sim) {
    for (auto node:this->nameToVar) {
        if (node.second->getSim() == sim) {
            return node.first;
        }
    }
    return "";
}

