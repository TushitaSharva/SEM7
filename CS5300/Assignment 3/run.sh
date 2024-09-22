#!/bin/bash

outputs_directory="./outputs"
if [ -n "$(ls -A "$outputs_directory")" ]; then
    rm "$outputs_directory"/*
fi

# To run for a particular file
# input_file_name="inp.txt"
# g++ -std=c++17 Bakery-CS21BTECH11022.cpp && ./a.out "$input_file_name"
# g++ -std=c++17 Filter-CS21BTECH11022.cpp && ./a.out "$input_file_name"

# To loop through all files in the subfolders of the 'testcases' directory and run all the test cases
# for subdirectory in ./inputs/*; do
#     echo "EXPERIMENT $subdirectory"
#     for input_file_name in $subdirectory/*.txt; do
#         g++ -std=c++17 Bakery-CS21BTECH11022.cpp && ./a.out "$input_file_name"
#         g++ -std=c++17 Filter-CS21BTECH11022.cpp && ./a.out "$input_file_name"
#     done
#     echo "---------------------------------------------------"
# done


# To loop through all files in the subfolders of the 'testcases' directory and run all the test cases five times
for input_file_name in ./inputs/*/*.txt; do
    echo "Experiment: $input_file_name"
    for i in {1..5}; do
        g++ -std=c++17 Bakery-CS21BTECH11022.cpp && ./a.out "$input_file_name"
    done
    for i in {1..5}; do
        g++ -std=c++17 Filter-CS21BTECH11022.cpp && ./a.out "$input_file_name"
    done
    echo "---------------------------------------------------"
done