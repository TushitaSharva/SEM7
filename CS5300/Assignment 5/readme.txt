PROGRAMMING ASSIGNMENT 5
JANGA TUSHITA SHARVA
CS21BTECH11022

-----------------------------------------------------------------

This directory consists of the following files:
 - Src-cs21btech11022.pdf
 - readme.txt
 - inp.txt
 - run.sh

And following sample folder
 - outputs

-----------------------------------------------------------------

'inp.txt' is a sample input file. The file contains
information, as given in the problem statement. 


NOTE:
- C++17 is required to run this, because template functions are  used.
- There must be inp.txt which aligns with above conditions. I have kept an inp.txt in this folder which can be modified.
- There must be a folder `outputs`. I have submitted this too, along with some sample output files inside the folder.
- After programs are executed, the outputs will be in the outputs folder, so as to prevent any confusion
- Everytime the programs are executed, the files in the outputs folder are deleted by the script itself if there are any.

-----------------------------------------------------------------
EXECUTION INSTRUCTIONS
-----------------------------------------------------------------
This directory contains a bash script "run.sh". To run this
file,
Change the permissions of the executable 
 - chmod u+x run.sh
Run the script
 - ./run.sh
 By default, the input file will be ``inp.txt`` in the same folder as the programs. 
 - To change the name of the file, change the `input_file_name` at line 9.

NOTE THAT GIVEN THE PROBLEM STATEMENT, THE PROGRAM WILL NOT TERMINATE IF THERE ARE PENDING DEPOSITS.
THE LOG FILES CAN BE REFERRED TO SEE THE PENDING DEPOSISTS.

- Click Ctrl+C to pause the execution if there are pending deposits and is not halting.

-----------------------------------------------------------------
To see the log files, go to the outputs folder. The output file would be named as out.txt.
-----------------------------------------------------------------

To execute only one file at a time, you may comment out any of those lines or follow these steps:
Open the commandline and open the current directory.
    $ g++ -std=c++17 Src-cs21btech11022.cpp && ./a.out "$input_file_name"

REMEBER TO DELETE THE OUTPUT FILES IF YOU ARE NOT RUNNING THE SCRIPT. 
ELSE THE PREVIOUS FILES GET APPENDED, AND MIGHT MISLEAD THAT RESULTS ARE WRONG.