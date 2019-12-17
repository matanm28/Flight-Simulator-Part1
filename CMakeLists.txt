cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex3 Command.h main.cpp Lexer.cpp Lexer.h Server.cpp Server.h cmake-build-debug/Client.cpp cmake-build-debug/Client.h SymbolTable.cpp SymbolTable.h)