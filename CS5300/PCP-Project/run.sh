#!/bin/bash

outputs_directory="./outputs"
if [ -n "$(ls -A "$outputs_directory")" ]; then
    rm "$outputs_directory"/*
fi

# input_file_name="inp.txt"
# g++ -std=c++17 seq.cpp && ./a.out "$input_file_name"

# To loop through all files in the subfolders of the 'testcases' directory and run all the test cases
# input_file_name="./inputs/a100.txt"
# g++ -std=c++17 parallel_dynamic.cpp && ./a.out "$input_file_name"
# echo "--------------------------------"
# g++ -std=c++17 parallel_chunk.cpp && ./a.out "$input_file_name"
# echo "--------------------------------"
# g++ -std=c++17 sequential.cpp && ./a.out "$input_file_name"
# echo "--------------------------------"
# echo "========================================================="

for input_file_name in ./inputs/E1/*.txt; do
    echo "$input_file_name"
    g++ -std=c++17 parallel_dynamic.cpp && ./a.out "$input_file_name"
    echo "--------------------------------"
    g++ -std=c++17 parallel_chunk.cpp && ./a.out "$input_file_name"
    echo "--------------------------------"
    g++ -std=c++17 sequential.cpp && ./a.out "$input_file_name"
    echo "========================================================="
done

for input_file_name in ./inputs/E2/*.txt; do
    echo "$input_file_name"
    g++ -std=c++17 parallel_dynamic.cpp && ./a.out "$input_file_name"
    echo "--------------------------------"
    g++ -std=c++17 parallel_chunk.cpp && ./a.out "$input_file_name"
    echo "--------------------------------"
    g++ -std=c++17 sequential.cpp && ./a.out "$input_file_name"
    echo "========================================================="
done