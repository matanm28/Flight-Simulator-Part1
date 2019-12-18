//
// Created by sapir on 17/12/2019.
//

#include "ConnectCommand.h"
#include <algorithm>

int ConnectCommand::execute(vector<string>::iterator &iter) {
    advance(iter, 2);
    return 3;
}
