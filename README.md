# OS-HW2-Sean-Shea
Assignment 2 for Operating Systems

# Files
bankers_alg.cpp: a program that takes an input file of a system snapshot and uses the Banker's Algorithm to determine if the system is in a safe state, and outputs the Safety Sequence if it is.

resources.txt: a text file formatted correctly to represent a system snapshot to be used in the bankers_alg program.

# Usage Instructions
To run the program, type the following command to compile it:

g++ bankers_alg.cpp -o bankers_alg

Then, to run the program, type the following command:

./bankers_alg

The program will start and ask for an input file. To use the provided file with the program, type:

resources.txt

Alternatively, you may type a file path of a different .txt file of your choice that is properly formatted.

# Input File Format
The input file can be changed if desired, as long as you keep the format the same.

The file must contain three tables, each with headings of "ALLOCATED", "MAX", and "AVAILABLE".

For the ALLOCATED table, each new line in the file represents a different process being added. The lines must contain the resource allocations for each process, separated by commas (the last resource should not have a comma). After the last process line, the string "END" should be typed.

The MAX Table is formatted the same as the ALLOCATED table.

The AVAILABLE table is similar, but only needs one line, so it is not necessary to add the "END" string to denote the end of the table.

Ensure that there are no empty lines within the tables, and that the ALLOCATED and MAX tables have the same dimensions, and that the AVAILABLE table has the same number of resources as the other two tables.
