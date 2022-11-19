/*
Author: Mai Tran
Course: COSC 2425
Quiz 3 EC
Reference:
    I use string parsing code from this forum:
    https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// size of table
const int SIZE = 56;

// code
const string CODE[] = { "81", "82", "83", "84", "85", "86", "87", "88", "89", "91", "92", "93", "94",
                    "95", "96", "97", "98", "99", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9",
                    "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "D1", "D2", "D3", "D4" ,
                    "D5", "D6", "D7", "D8", "D9", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9",
                    "40", "4B", "6B", "5A" };

// decode value               	 
const char DECODE[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                    ' ',  '.',  ',',  '!' };


int main() {


    // get number of code
    int codeNum = 0;
    cout << "Enter number of code: ";
    cin >> codeNum;


    // only get number greater than 0
    while (codeNum <= 0) {

        cout << "Please enter positive numbers only.\n";
        cout << "Enter number of code: ";
        cin >> codeNum;
    }


    // get a string of code
    cin.ignore();
    string input;
    cout << "Enter the codes: ";
    getline(cin, input);


    // get individual code that is separated by space
    // vector to hold individual code
    vector<string> codes;
    int pos = 0;
    string delimiter = " ";
    string token;

    // get token order from 0 to n-1
    while ((pos = input.find(delimiter)) != string::npos) {

        token = input.substr(0, pos);
        codes.push_back(token);
        input.erase(0, pos + delimiter.length());

    }

    // get the last token
    token = input.substr(0, input.length());
    codes.push_back(token);


    // translation codes
    cout << "\nTranslated code in ASCII: \n";
    for (int i = 0; i < codeNum; i++) {


        for (int index = 0; index < SIZE; index++) {


            if (CODE[index] == (codes[i])) {

                cout << DECODE[index];

            }
        }
    }

    cout << endl;
}


