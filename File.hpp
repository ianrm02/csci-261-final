#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//prototypes
string getFilename();
bool fileOpen(ifstream& fileIn, const string fileName);
void fileClose(ifstream& fileIn);

//definitions
//Gets desired file name from user in the form of a string
string getFilename() {
    cout << "What file do you wish to open: ";
    string fileName;
    cin >> fileName;
    return fileName;
}
//Opens desired file and returns a bool so the program can quit if the file open is not successful
bool fileOpen(ifstream& fileIn, const string fileName) {
    fileIn.open(fileName);
    if (!fileIn) {
        cerr << "Error: failed to open file." << endl;
        return false;
    }
    return true;
}
//Closes desired file to clean up memory
void fileClose(ifstream& fileIn) {
    fileIn.close();
}