# Sudoku Solver!

**Installation**

No dependencies other than the c standard library. It uses no dynamic libraries.

**Usage**

Pass file path to sudoku puzzle as command line parameter.

It parses a file by skipping whitespace and commas. It reads numbers as the hints (except 0 which it interprets as a 
letter), and interprets non-whitespace and non-numeric characters as empty squares. 

Using -o \<FILENAME\> will cause the program to write its solution to \<FILENAME\>

