#!/bin/bash

outputs_directory="./outputs"
if [ -n "$(ls -A "$outputs_directory")" ]; then
    rm "$outputs_directory"/*
fi

# To run for a particular file
input_file_name="inp.txt"
g++ -std=c++17 Src-cs21btech11022.cpp && ./a.out "$input_file_name"