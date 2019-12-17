cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex3 Commands/Command.h Commands/Command.cpp main.cpp Commands/OpenServerCommand.cpp Commands/OpenServerCommand.h baseInclude.h)