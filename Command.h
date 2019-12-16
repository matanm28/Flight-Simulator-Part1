//
// Created by matan on 12/16/19.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H


class Command {
public:
    virtual int execute() = 0;

    virtual ~Command() = default;
};


#endif //EX3_COMMAND_H
