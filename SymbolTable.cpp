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
    this->mapOfVar.insert({varName, new Var(value, sim, direction)});
}

void SymbolTable::addVar(string varName, string sim, string direction) {
    this->mapOfVar.insert({varName, new Var(sim, direction)});
}

void SymbolTable::addVar(string varName, float value) {
    this->mapOfVar.insert({varName, new Var(value)});
}

void SymbolTable::addVar(string varName, Var *var) {
    this->mapOfVar.insert({varName, var});
}


void SymbolTable::setVar(string varName, float value) {
    this->mutexLock.lock();
    mapOfVar.find(varName)->second->setValue(value);
    this->mutexLock.unlock();
}

Var SymbolTable::getVar(string varName) {
    if (this->mapOfVar.find(varName) != this->mapOfVar.cend()) {
        return *this->mapOfVar.find(varName)->second;
    } else {
        return NULL;
    }
}

string SymbolTable::varExists(string sim) {
    for (auto node:this->mapOfVar) {
        if (node.second->getSim() == sim) {
            return node.first;
        }
    }
    return "";
}

