/*
Author: Mai Tran
Course: COSC 2425
Quiz 2 Extra Credit
Reference:
I got help from the following websites:
+ How to add a character to the beginning of string (http://www.cplusplus.com/forum/beginner/16761/)
+ How to convert from integer to string(https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c)
+ I used the decimal to binary algorithm from the Quiz 1 extra credit
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;


// lower and upper bound
const int MIN = 1;
const int MAX = 9;


// function to display the first line (which is variable's name line)
void dis1Line(int varNum) {

    // hold variables name, begin with 'A'
    char start = 'A';


    cout << setw(4) << " ";
    // if there is only one variables, don't add '|'
    if (varNum == 1) {

        cout << start;

        // if there are more than 1 variable add "|" as a separator
    }
    else {

        for (int i = 0; i < varNum; i++) {

            // display variable then increase its ASCII code by one
            cout << start++;

            // if there are 4 variables, there should be 4 - 1 = 3 separators
            if (i < varNum - 1) {

                cout << "|";

            }

        }
    }

    cout << endl;

}


// input validation, return false if number input out of range (1-9)
bool isValid(int varNum) {

    if (varNum < MIN || varNum > MAX) {

        cout << "Please enter numbers in range of 1-9 only\n";
        return (false);
    }

    // if the previous condition fail, return true;
    return (true);
}


// function to convert from int to binary string, each elements separated by '|'
// binary string is also a form of all boolean input for specific iteration  
void display2(const int varNum, const int decimal) {

    int temp = decimal;

    // hold 0/1 combinations for each iteration
    string output;

    // decimal to binary algorithm
    for (int i = 0; i < varNum; i++) {

        int binary = temp % 2;

        output = to_string(binary) + output;

        if (i < varNum - 1) {

            output = "|" + output;
        }

        temp /= 2;

    }

    // display converted && formatted binary string
    cout << output;
}


int main() {

    // hold number of variables
    int varNum;

    // prompt for user's input
    cout << "\nEnter the number of the variables: ";
    cin >> varNum;
    cout << endl;

    // call validation checking function, only continue if true
    if (isValid(varNum)) {

        // display the variable's name line
        dis1Line(varNum);

        // loop to go through all possible combination
        for (int i = 0; i < pow(2, varNum); i++) {

            cout << setw(4) << left << i + 1;

            // display boolean input for each iteration
            display2(varNum, i);

            cout << endl;

        }
    }


    // terminate program
    return 0;
}
