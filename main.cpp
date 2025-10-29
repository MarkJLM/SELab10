//String Addition Program
//No external sources used.
//Created 10/29/25 Mark Lammers-Meis

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    //Open a file
    string fileName;
    cout << "Input file name: ";
    cin >> fileName;
    ifstream noFile(fileName);
    if (!noFile.is_open()) {
        cout << "No file is there." << endl;
        return 0;
    }
    
    string fileLine;
    string no1;
    string no2;
    char sign = 0;
    char decimal = 0;
    //Start reading lines
    while (getline(noFile, fileLine)) {
        sign = 0;
        decimal = 0;
        //Check every character in the input string
        for (int j = 0; j < fileLine.length(); j ++) {
            if (fileLine[j] == 46 && !decimal) {
                decimal = 1;
            } else {
                cout << "This is bad." << endl;
                break;
            }
        }
    }
    noFile.close();
    return 0;
}
