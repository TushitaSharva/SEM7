#!/bin/bash

outputs_directory="./outputs"
if [ -n "$(ls -A "$outputs_directory")" ]; then
    rm "$outputs_directory"/*
fi

g++ -std=c++14 Assgn1-Chunk-CS21BTECH11022.cpp -pthread && ./a.out
g++ -std=c++14 Assgn1-Mixed-CS21BTECH11022.cpp -pthread && ./a.out
g++ -std=c++14 Assgn1-Dynamic-CS21BTECH11022.cpp -pthread && ./a.out
g++ -std=c++14 Assgn1-ExtraCredit-CS21BTECH11022.cpp -pthread && ./a.out