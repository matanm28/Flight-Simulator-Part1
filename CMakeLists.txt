cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex3 Commands/Command.h Commands/Command.cpp Commands/OpenServerCommand.h Commands/OpenServerCommand.cpp main.cpp Lexer.cpp Lexer.h Server.cpp Server.h SymbolTable.cpp SymbolTable.h InitializeCommands.cpp InitializeCommands.h Commands/ConnectCommand.cpp Commands/ConnectCommand.h Commands/DefineVarCommand.cpp Commands/DefineVarCommand.h Commands/PrintCommand.cpp Commands/PrintCommand.h Commands/SleepCommand.cpp Commands/SleepCommand.h Commands/ConditionParser.h Commands/IfCommand.cpp Commands/IfCommand.h Commands/LoopCommand.cpp Commands/LoopCommand.h Var.cpp Var.h)