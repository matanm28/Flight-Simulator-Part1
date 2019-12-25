//
// Created by sapir on 17/12/2019.
//

#include "SymbolTable.h"

SymbolTable *SymbolTable::unifiedSymbolTable = nullptr;

SymbolTable::SymbolTable() {
    //empty or not?
}

SymbolTable *SymbolTable::getSymbolTable() {
    if (unifiedSymbolTable == nullptr) {
        unifiedSymbolTable = new SymbolTable();
    }
    return unifiedSymbolTable;
}

void SymbolTable::addVar(string varName, string sim, string direction, float value) {
    Var *var = new Var(value, sim, direction);
    this->nameToVarLock.lock();
    this->nameToVar.insert({varName, var});
    this->nameToVarLock.unlock();
    this->simToVarLock.lock();
    this->simToVar.insert({sim, var});
    this->simToVarLock.unlock();

}

void SymbolTable::addVar(string varName, string sim, string direction) {
    this->addVar(varName, sim, direction, DEFAULT_VALUE);

}

void SymbolTable::addVar(string varName, float value) {
    Var *var = new Var(value);
    this->nameToVarLock.lock();
    this->nameToVar.insert({varName, var});
    this->nameToVarLock.unlock();
}


void SymbolTable::setVarByName(string varName, float value) {
    this->nameToVarLock.lock();
    if (this->nameToVar.find(varName) != this->nameToVar.cend()) {
        this->nameToVar.find(varName)->second->setValue(value);
    }
    this->nameToVarLock.unlock();
    if (!this->guiStarted) {
        this->guiStarted = true;
    }
}

void SymbolTable::setVarBySim(string sim, float value) {
    this->simToVarLock.lock();
    if (this->simToVar.find(sim) != this->simToVar.cend()) {
        if (this->simToVar.find(sim)->second->getDirection() == "<-") {
            this->simToVar.find(sim)->second->setValue(value);
        }
    }
    this->simToVarLock.unlock();
}


Var SymbolTable::getVar(string varName) {
    this->nameToVarLock.lock();
    if (this->nameToVar.find(varName) != this->nameToVar.cend()) {
        this->nameToVarLock.unlock();
        return *this->nameToVar.find(varName)->second;
    } else {
        this->nameToVarLock.unlock();
        return NULL;
    }
}

Var SymbolTable::getVarBySim(string sim) {
    this->simToVarLock.lock();
    if (this->nameToVar.find(sim) != this->nameToVar.cend()) {
        this->simToVarLock.unlock();
        return *this->simToVar.find(sim)->second;
    } else {
        this->simToVarLock.unlock();
        return NULL;
    }
}

string SymbolTable::varExists(string sim) {
    this->simToVarLock.lock();
    for (auto node:this->nameToVar) {
        if (node.second->getSim() == sim) {
            this->nameToVarLock.unlock();
            return node.first;
        }
    }
    this->simToVarLock.unlock();
    return "";
}

vector<Var *> SymbolTable::getNameToVar() {
    vector<Var *> varVector;
    for (auto node : this->nameToVar) {
        varVector.push_back(node.second);
    }
    return varVector;
}

bool SymbolTable::getGuiStarted() {
    return this->guiStarted;
}


