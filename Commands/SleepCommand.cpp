//
// Created by sapir on 17/12/2019.
//

#include "SleepCommand.h"

int SleepCommand::execute(vector<string>::iterator &iter) {
    iter++;
    return 2;
}
