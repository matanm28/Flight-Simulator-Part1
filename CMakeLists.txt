cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex3 Commands/Command.h Commands/Command.cpp Commands/OpenServerCommand.h Commands/OpenServerCommand.cpp main.cpp Lexer.cpp Lexer.h Server.cpp Server.h Client.cpp Client.h SymbolTable.cpp SymbolTable.h Var.cpp Var.h)