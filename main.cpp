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
    
    //Create parsing variables
    string fileLine;
    string digits[2];
    char sign[2];
    char decPoint[2];
    char noIndex[2];
    char onNum = 0;
    
    string output = "";
    char shift[2];
    int addResult;
    int carry;
    
    char leading = 0;
    char trailing = 0;
    char outSign = 1;
    char invertStop = 0;
    
    //Start reading lines
    while (getline(noFile, fileLine)) {
        //Reset variables
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
            if (fileLine[j] == 46 && !decPoint[onNum] && noIndex[onNum] > 0 && j < fileLine.length() - 1) {
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
                //Indicate an error
                onNum = 2;
                break;
            }
        }
        
        //Create output
        if (onNum == 1) {
            output = "";
            //Align decimal points in numbers
            decPoint[0] = decPoint[0]?decPoint[0]:digits[0].length();
            decPoint[1] = decPoint[1]?decPoint[1]:digits[1].length();
            shift[0] = (decPoint[0] < decPoint[1])?(decPoint[1]-decPoint[0]):0;
            shift[1] = (decPoint[1] < decPoint[0])?(decPoint[0]-decPoint[1]):0;
            decPoint[0] += shift[0];
            
            //Add leading 0s
            for (int i = 0; i < shift[0]; i ++) {
                digits[0] = '0' + digits[0];
            }
            for (int i = 0; i < shift[1]; i ++) {
                digits[1] = '0' + digits[1];
            }
            
            //Add trailing 0s
            while (digits[0].length() < digits[1].length()) {
                digits[0] += '0';
            }
            while (digits[1].length() < digits[0].length()) {
                digits[1] += '0';
            }
            
            //Add numbers
            carry = 0;
            for (int i = digits[0].length() - 1; i >= 0; i --) {
                //Calculate new digit
                addResult = 20 + ((sign[0]==2)?-1:1)*(digits[0][i]-48) + ((sign[1]==2)?-1:1)*(digits[1][i]-48) + carry;
                carry = addResult/10-2;
                output = (char)(addResult%10 + 48) + output;
            }
            
            //Handle overflow carry
            outSign = 1;
            if (carry > 0) {
                output = (char)(carry + 48) + output;
                decPoint[0] ++;
            } else if (carry < 0) {
                //If the result is negative, invert all of it
                carry = -carry;
                output = '0' + output;
                decPoint[0] ++;
                
                //Find last 0s
                invertStop = 0;
                for (int i = output.length()-1; i >= 0; i --) {
                    if (output[i] == 48) {
                        invertStop ++;
                    } else {
                        break;
                    }
                }
                output[0] = carry - output[0] + 95;
                for (int i = 1; i < output.length()-invertStop-1; i ++) {
                    output[i] = 105 - output[i];
                }
                output[output.length()-invertStop-1] = 106 - output[output.length()-invertStop-1];
                outSign = 2;
            }
            
            //Find leading 0s
            leading = 0;
            for (int i = 0; i < output.length()-1; i ++) {
                //Count leading 0s
                if (output[i] == 48 && decPoint[0] > i+1) {
                    leading ++;
                } else {
                    break;
                }
            }
            
            //Find trailing 0s
            trailing = 0;
            for (int i = output.length()-1; i > leading; i --) {
                //Count trailing 0s
                if (output[i] == 48) {
                    trailing ++;
                } else {
                    break;
                }
            }
            
            //Print sum
            if (outSign == 2) {
                cout << "-";
            }
            for (int i = leading; i < output.length()-trailing; i ++) {
                //Add decimal point
                if (i == decPoint[0]) {
                    cout << '.';
                }
                cout << output[i];
            }
            cout << endl;
        } else {
            cout << "This is bad." << endl;
        }
    }
    noFile.close();
    return 0;
}
