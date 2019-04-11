#!/bin/bash

echo running c++ program
gcc main.cpp logparsing.cpp -o MainLoop -std=c++11 -lstdc++

# For running the programm

./MainLoop

