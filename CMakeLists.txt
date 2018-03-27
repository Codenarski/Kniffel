cmake_minimum_required(VERSION 3.9)
project(Kniffel3)

set(CMAKE_CXX_STANDARD 11)

add_executable(Kniffel3
        Die.c
        Die.h
        main.c
        Player.c
        Player.h
        Scorecard.c
        Scorecard.h)
