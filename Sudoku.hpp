#pragma once
//std headers
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
//my headers
#include "File.hpp"

class Sudoku {
    private:
        //member values
        int sudokuGrid[9][9];
        //helper functions
        bool inRow(const unsigned int row, const unsigned int num);
        bool inCol(const unsigned int col, const unsigned int num);
        bool inBox(const int boxRowStart, const int boxColStart, const int num);
        bool isEmpty(int &row, int &col);
        bool isValid(const int row, const int col, const int num);
    public:
        //constructor/destructor
        Sudoku();
        ~Sudoku();
        //setters and getters
        void setSudokuGrid(const unsigned int height, const unsigned int width, const unsigned int value);
        int getSudokuGrid(const unsigned int height, const unsigned int width);
        bool setSudokuGridVal(ifstream& fileIn);
        //main program functions
        bool checkSudokuGrid();
        bool solveSudokuGrid();
        void printSudokuGrid();
};

//definitions
//constructor
Sudoku :: Sudoku() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            setSudokuGrid(row, col, 0);
        }
    }
}
//destructor
Sudoku :: ~Sudoku() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            setSudokuGrid(row, col, 0);
        }
    }
}
//sets value at specific grid point
void Sudoku :: setSudokuGrid(const unsigned int height, const unsigned int width, const unsigned int value) {
    sudokuGrid[height][width] = value;
    return;
}
//gets value at specific grid point
int Sudoku :: getSudokuGrid(const unsigned int height, const unsigned int width) {
    return sudokuGrid[height][width];
}
//creates the puzzle itself from the input file
bool Sudoku :: setSudokuGridVal(ifstream& fileIn) {
    char c;
    for (int h = 0; h < 9; h++) {
        for (int w = 0; w < 9; w++) {
            fileIn.get(c); //gets one character and ignores if newline
            if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '\n') 
                return false;
            while (c == '\n') 
                fileIn.get(c);
            sudokuGrid[h][w] = (int)c - 48;
        }
    }
    return true;
}
//prints the given grid
void Sudoku :: printSudokuGrid() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0 && col != 0)
                cout << " | "; //included for aesthetics
            cout << sudokuGrid[row][col] << " ";
        }
        if (row - 2 == 0 || row - 5 == 0)
            cout << endl << "------- ------- -------"; //included for aesthetics
        cout << endl;
    }
}
//checks if num can be used in row
bool Sudoku :: inRow(const unsigned int row, const unsigned int num) {
    for (int col = 0; col < 9; col++)
        if (sudokuGrid[row][col] == num)
            return true;
    return false;
}
//checks if num can be used in col
bool Sudoku :: inCol(const unsigned int col, const unsigned int num) {
    for (int row = 0; row < 9; row++)
        if (sudokuGrid[row][col] == num)
            return true;
    return false;
}
//checks if num can be used in box (3x3)
bool Sudoku :: inBox(const int boxRowStart, const int boxColStart, const int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (sudokuGrid[row+boxRowStart][col+boxColStart] == num) //checks 3x3 box
                return true;
   return false;
}
//checks if location is empty
bool Sudoku :: isEmpty(int &row, int &col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (sudokuGrid[row][col] == 0)
                return true;
    return false;
}
//checks if num can be used in location
bool Sudoku :: isValid(const int row, const int col, const int num) {
    return !inRow(row, num) && !inCol(col, num) && !inBox(row - row%3, col - col%3, num); //determines which of the '3x3' boxes the point is in
}
//validate the original grid
bool Sudoku :: checkSudokuGrid() {
    int num;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            num = sudokuGrid[row][col];
            sudokuGrid[row][col] = 0;
            if (num == 0) //if empty skip
                continue;
            else if (!isValid(row, col, num)) //if invalid before the process has begun -> exit program
                return false;
            sudokuGrid[row][col] = num;
        }
    }
    return true;
}
//solve the sudoku grid
bool Sudoku :: solveSudokuGrid() {
    int row, col;
    if (!isEmpty(row, col))
        return true; //all spaces filled (base case)
    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) { 
            sudokuGrid[row][col] = num;
            if (solveSudokuGrid()) //recursive call to go through all places within grid
                return true;
            sudokuGrid[row][col] = 0;
        }
    }
    return false;
}