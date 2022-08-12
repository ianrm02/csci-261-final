/* CSCI 261: Final Project
 *
 * Section C
 * 
 * Author: Ian Marchbank
 * 
 * RESOURCES USED (Office Hours, Tutoring, Other Students, etc & in what capacity):
 * - Went to office hours and had help creating psuedocode and determining wat funtions would be necessary
 * - Asked for help from section porfessor for how to validate box and create the validation function
 * - Went to office hours and asked for help understanding recirsive functions and writing psuedocode for my function
 * 
 * DESCRIPTION:
 * This program is designed to take in a sudoku puzzle and solve it if possible.
 * This program takes in a '.txt' file of a 9x9 grid of integers that corresponds to a sudoku puzzle.
 * This program then determines if the puzzle can be solved and if so solves the puzzle for the user.
 * 
 * More information/instructions avaible in 'final.txt'
 */

//std headers
#include <string>
#include <iostream>
using namespace std;
//my headers
#include "File.hpp"
#include "Sudoku.hpp"

int main(int argc, char* argv[]) {
    // get filename to open
    string filename;
    cout << endl << "Welcome to \'Sudoku Solver\'!" << endl;
    cout << "Submit a file as intructed in the comments!" << endl << endl;
    if(argc == 1) {
        filename = getFilename();
    } else if(argc == 2) {
        filename = argv[1];
    } else {
        cerr << "Usage: " << argv[0] << " [filename]" << endl;
        cerr << "  filename   - optional file to open upon start" << endl;
        return -2;
    }

    //opening and verifying file
    ifstream fileIn;
    if(!fileOpen(fileIn, filename))
        return -1;
    cout << "File opened successfully!" << "\n" << "\n";

    //make sudoku array
    Sudoku puzzleToSolve;
    if (!puzzleToSolve.setSudokuGridVal(fileIn)) {
        cout << "The grid is invalid and cannot be solved, sorry!" << endl << endl;
        return -1;
    }

    //validate the puzzle
    if (!puzzleToSolve.checkSudokuGrid()) {
        cout << "The grid is invalid and cannot be solved, sorry!" << endl << endl;
        return -1;
    }

    //solve sudoku array and print if solve
    if (puzzleToSolve.solveSudokuGrid() == true) {
        cout << "The sudoku puzzle was able to be solved!" << endl;
        cout << "The final result is..." << endl << endl;
        puzzleToSolve.printSudokuGrid();
        cout << endl;
    }
    else
        cout << "The sudoku puzzle was unable to be solved!" << endl;

    //close all files and clean memory
    fileClose(fileIn);
    puzzleToSolve.~Sudoku();

    //end program
    cout << "Thank you!" << endl << endl;
    return 0;
}