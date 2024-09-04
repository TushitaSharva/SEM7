#!/bin/bash

outputs_directory="./outputs"
if [ -n "$(ls -A "$outputs_directory")" ]; then
    rm "$outputs_directory"/*
fi

# To run for a particular file
# input_file_name="inp.txt"
# g++ -std=c++14 Assgn2-Chunk-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"
# g++ -std=c++14 Assgn2-Mixed-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"
# g++ -std=c++14 Assgn2-Dynamic-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"

# To loop through all files in the subfolders of the 'testcases' directory and run all the test cases
for input_file_name in ./testcases/*/*.txt; do
    g++ -std=c++14 Assgn2-Chunk-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"
    g++ -std=c++14 Assgn2-Mixed-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"
    g++ -std=c++14 Assgn2-Dynamic-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"
done