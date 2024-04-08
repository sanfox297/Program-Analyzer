## Program-Analyzer

The Program Analyzer is a C++ program that analyzes a given program file and extracts available expressions and live variables. It implements traditional techniques such as iterative algorithms to identify which expressions are available and which variables are live at various program points.

# Features

- Extracts available expressions from the program
- Identifies live variables at different program points
- Supports variable assignments, expressions, and variable declarations
- Handles common C++ data types (int, double, float, char, bool)

# Usage

1. Compile the program using the following command:

	g++ main.cpp -o main


2. Run the program, providing the program file as an argument:

	./main test.cpp

3. The program will analyze the input program file and display the available expressions and live variables in the console.
