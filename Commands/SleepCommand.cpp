//
// Created by sapir on 17/12/2019.
//

#include "SleepCommand.h"

int SleepCommand::execute(vector<string>::iterator &iter) {
    int time;
    Interpreter interpreter;
    try {
        time = (int) interpreter.interpret(*iter)->calculate();
    } catch (char *c) {
        time = 0;
    } catch (exception *e) {
        time = 0;
    }
    this_thread::sleep_for(chrono::milliseconds(time));
    iter++;
    return 2;
}
