//
// Created by sapir on 17/12/2019.
//

#include "SleepCommand.h"

int SleepCommand::execute(vector<string>::iterator &iter) {
    int time;
    try {
        time = stoi(*iter);
    } catch (exception *e) {
        time = 0;
    }
    this_thread::sleep_for(chrono::milliseconds(time));
    iter++;
    return 2;
}
