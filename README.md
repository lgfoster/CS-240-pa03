# CS-240-pa03
This homework assignment is based upon a mock "batch" system, where the program accepts a batch file that contains various commands and executes them using children processes.

There is a massive bug in the code, specifically with the exit() function that the child process uses to return. If there are numerous bad commands input into the program, the children that fail to execute the command will mimic an fseek() to beginning of file, causing the program to go infinite. 
