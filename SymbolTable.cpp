//
// Created by sapir on 17/12/2019.
//

#include "SymbolTable.h"


SymbolTable::SymbolTable() {

}

bool SymbolTable::updateSymboleTable(double value, int varIndex) {
    this->mutexLock.lock();

}

bool SymbolTable::updateSymboleTable(vector<double> myNums) {
    return false;
}

void SymbolTable::buildSimStringArray() {
    simArr[magnetic] = string("/controls/switches/magnetos");
    simArr[throttle] = string("/controls/engines/current-engine/throttle");
}
