PROGRAMMING ASSIGNMENT 2 : MEASURING MATRIX SPARSITY USING OPENMP
JANGA TUSHITA SHARVA
CS21BTECH11022

-----------------------------------------------------------------

This directory consists of the following files:
 - Assgn2-Chunk-CS21BTECH11022.cpp
 - Assgn2-Mixed-CS21BTECH11022.cpp
 - Assgn2-Dynamic-CS21BTECH11022.cpp
 - Assgn2-Report-CS21BTECH11022.cpp
 - Assgn2-ReadMe-CS21BTECH11022.cpp
 - inp.txt
 - run.sh

-----------------------------------------------------------------

'inp.txt' is a sample input file. The file contains
the following information, as mentioned in the problem statement. 
The first line contains four numbers (seperated by space)
 - N: Number of rows in matrix
 - S: Sparsity of the matrix
 - K: Number of threads
 - rowInc: For Dynamic Approach
 Following N lines have the input matrix for which we have to calculate sparsity for.


NOTE:
- There must be inp.txt which aligns with above conditions. I have kept an inp.txt in this folder which can be modified.
- There must be a folder `outputs`. I have submitted this too, along with some sample output files inside the folder.
- After programs are executed, the outputs will be in the outputs folder, so as to prevent any confusion
- Everytime the programs are executed, the files in the outputs folder are deleted by the script itself if there are any.

-----------------------------------------------------------------
EXECUTION INSTRUCTIONS
-----------------------------------------------------------------

(I) METHOD 1: All files for one input file at a time
This directory contains a bash script "run.sh". To run this
file,
Change the permissions of the executable 
 - chmod u+x run.sh
Run the script
 - ./run.sh
 By default, the input file will be ``inp.txt`` in the same folder as the programs. 
 - To change the name of the file, change the `input_file_name` at line 9.


(II) METHOD 2: Run all testcases at a time
Steps: 
(1) Comment the lines 9 to 12 in run.sh file
(2) Uncomment the lines 15 to 19 in the run.sh file
(3) Make sure that all the testcases are present in the subfolders of the folder testcases.

|---- Assgn2-Chunk-CS21BTECH11022.cpp
|---- Assgn2-Mixed-CS21BTECH11022.cpp
|---- Assgn2-Dynamic-CS21BTECH11022.cpp
|---- inp.txt
|---- outputs
|    |---- (might be empty, or there might be files)
|---- run.sh
|---- testcases
|    |---- E1
|    |    |---- .txt files with any name
|    |---- E2
|    |    |---- .txt files with any name
|    |---- E3
|    |---- E4
|    |---- And so on with above structure


All the text files under the subfolders will be run. Note that the log files would be appended for all executions in this loop.

-----------------------------------------------------------------

To see the log files, go to the outputs folder. The output files would be named as out_<implementation>.txt, 
Debug files that are to be ignored are written as debug_<implementation>.txt
Along with this, the time taken for implementation would also be printed to the console.

-----------------------------------------------------------------

To execute only one file at a time, you may comment out any of those lines or follow these steps:
Open the commandline and open the current directory.
- For chunk:
    $ g++ -std=c++14 Assgn2-Chunk-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"
- For mixed:
    $ g++ -std=c++14 Assgn2-Mixed-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"
- For dynamic:
    $ g++ -std=c++14 Assgn2-Dynamic-CS21BTECH11022.cpp -fopenmp -lm && ./a.out "$input_file_name"

REMEBER TO DELETE THE OUTPUT FILES IF YOU ARE NOT RUNNING THE SCRIPT. ELSE THE PREVIOUS FILES GET APPENDED, AND MIGHT MISLEAD THAT RESULTS ARE WRONG.