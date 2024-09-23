PROGRAMMING ASSIGNMENT 3 : IMPLEMENTING BAKERY AND FILTER LOCKS
JANGA TUSHITA SHARVA
CS21BTECH11022

-----------------------------------------------------------------

This directory consists of the following files:
 - Bakery-CS21BTECH11022.cpp
 - Filter-CS21BTECH11022.cpp
 - Assgn3-Report-CS21BTECH11022.pdf
 - readme.txt
 - inp.txt
 - run.sh

ANd following sample folders
 - outputs
 - inputs

-----------------------------------------------------------------

'inp.txt' is a sample input file. The file contains
the following information, as mentioned in the problem statement. 
The first line contains four numbers (seperated by space)
 - n: Number of threads
 - k: Number of times entering into critical section
 - lamda1: For simulaing behaviour inside critical section
 - lambda2: Forsimulating behavious outside critical section


NOTE:
- C++17 is required to run this, because template functions are  used.
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
(2) Uncomment the lines 14 to 21 in the run.sh file
(3) Make sure that all the testcases are present in the subfolders of the folder testcases.

|---- Bakery-CS21BTECH11022.cpp
|---- Filter-CS21BTECH11022.cpp
|---- Assgn3-Report-CS21BTECH11022.pdf
|---- readme.txt
|---- inp.txt
|---- outputs
|    |---- (might be empty, or there might be files)
|---- run.sh
|---- inputs
|    |---- 1
|    |    |---- .txt files with any name
|    |---- 2
|    |    |---- .txt files with any name
|    |---- 3
|    |---- 4
|    |---- And so on with above structure


All the text files under the subfolders will be run. NOTE that the log files would be appended for all executions in this loop.
This is meant for checking scalability for program running with ease.
For reference, I had uploaded the sample input folder I used for the experiments for the report.
-----------------------------------------------------------------

To see the log files, go to the outputs folder. The output files would be named as out_<implementation>.txt, 
Debug files that are to be ignored are written as debug_<implementation>.txt
Along with this, throughput, average time, and worst time are printed to the console.

-----------------------------------------------------------------

To execute only one file at a time, you may comment out any of those lines or follow these steps:
Open the commandline and open the current directory.
- For Filter:
    $ g++ -std=c++17 Filter-CS21BTECH11022.cpp && ./a.out "$input_file_name"
- For Bakery:
    $ g++ -std=c++17 Filter-CS21BTECH11022.cpp && ./a.out "$input_file_name"

REMEBER TO DELETE THE OUTPUT FILES IF YOU ARE NOT RUNNING THE SCRIPT. ELSE THE PREVIOUS FILES GET APPENDED, AND MIGHT MISLEAD THAT RESULTS ARE WRONG.