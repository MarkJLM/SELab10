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
    string digits[2];
    char sign[2];
    char decPoint[2];
    char noIndex[2];
    char onNum = 0;
    //Start reading lines
    while (getline(noFile, fileLine)) {
        digits[0] = "";
        digits[1] = "";
        sign[0] = 0;
        sign[1] = 0;
        decPoint[0] = 0;
        decPoint[1] = 0;
        noIndex[0] = 0;
        noIndex[1] = 0;
        onNum = 0;
        //Check every character in the input string
        for (int j = 0; j < fileLine.length(); j ++) {
            //If no sign is given, assume positive
            if (fileLine[j] != 43 && fileLine[j] != 45 && !sign[onNum]) {
                sign[onNum] = 1;
            }
            //Find decimal point
            if (fileLine[j] == 46 && !decPoint[onNum] && noIndex[onNum] > 0) {
                decPoint[onNum] = noIndex[onNum];
            //Find sign
            } else if (fileLine[j] == 43 && !sign[onNum]) {
                sign[onNum] = 1;
            } else if (fileLine[j] == 45 && !sign[onNum]) {
                sign[onNum] = 2;
            //Get digits
            } else if (fileLine[j] > 47 && fileLine[j] < 58) {
                digits[onNum] += fileLine[j];
                noIndex[onNum] ++;
            //Switch to second number
            } else if (fileLine[j] == 32 && digits[onNum].length() > 0) {
                onNum ++;
            } else {
                onNum = 2;
                break;
            }
        }
        if (onNum == 1) {
            cout << ((sign[0]==2)?'-':'+') << digits[0] << "/10^" << (int)decPoint[0] << endl;
            cout << ((sign[1]==2)?'-':'+') << digits[1] << "/10^" << (int)decPoint[1] << endl;
        } else {
            cout << "This is bad." << endl;
        }
    }
    noFile.close();
    return 0;
}
