#ifndef FILELOAD_H
#define FILELOAD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

vector<vector<string>> loadData(string filename) {
    fstream theFile; // creates an fstream object for theFile
    theFile.open(filename); //opens the file

    if (!theFile.is_open()) {
        cerr << "Error while opening file"; // print error message to standard error stream
        exit(1); 
    }

    vector<vector<string>> accountData; // vector<vector<string>> to store accountData

    int linecount = 0; 
    string line;
    while (getline(theFile, line)) {
        ++linecount; // increment linecount for each line

        stringstream ss(line); // create a stringstream object for each line
        vector<string> row;    // row -> a vector inside the vector to store each line

        string field;
        while (getline(ss, field, ',')) { // separate the data for each field and place it into row
            row.push_back(field);
        }
        accountData.push_back(row); // Add the row to the accountData vector
    }

    theFile.close(); // closes the file

    return accountData; // return the loaded data
}

void printData(const vector<vector<string>>& data) {
    for (const auto& row : data) { // const auto (to automatically determine data type),
                                   // and ampersand '&' to reference each element in accountData 
        for (const auto& field : row) {
            cout << field << "\t";
        }
        cout << endl;
    }
}

#endif // FILELOAD_H
