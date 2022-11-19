/*
Author: Mai Tran
Course: COSC: 2425
Quiz 5 EC
Reference:
   + I learned how to use bitwise operation in c++ from this website: https://www.programiz.com/cpp-programming/bitwise-operators
   + I used decimal to binary convert function from this website: https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
   + How to use stoi to convert binary back to decimal: https://www.geeksforgeeks.org/program-binary-decimal-conversion/
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// split command by space and push plitted words into vector
void refine(vector<string>& element, string input) {

    string temp;
    for (unsigned i = 0; i < input.size(); i++) {

        // temporary string to accumulate word
        if (input[i] != ' ') { temp += input[i]; };

        // add word to vector if encoutere space or end of string
        if (input[i] == ' ' || i == input.size() - 1) {


            element.push_back(temp);
            temp = "";
            continue;

        }
    }
}


// convert int into binary string
string toBinary(int n)
{
    string r;
    while (n != 0) {

        r = (n % 2 == 0 ? "0" : "1") + r;

        n /= 2;
    }
    return r;
}

int main()
{

    // run again flag
    char runAgain = 'N';

    do {

        // hold command, input from user
        string command;
        cout << "\nEnter the command: ";
        getline(cin, command);

        vector<string> element;
        // slip input by word and push int vector      
        refine(element, command);

        // hold resultant, initilized to -1
        int output = -1;

        // hold type of operation ("A" , "O", "X", ..etc)
        string operation = element[0];

        // if number of element in command is 2
        if (element.size() == 2) {

            // if this is a NOT command
            if (operation == "N") {

                // get decimal number
                int decimal = stoi(element[1]);

                // convert decimal number to binary string
                string bi = toBinary(decimal);

                // negate binary
                for (unsigned i = 0; i < bi.size(); i++) {
                    if (bi[i] == '0') {
                        bi[i] = '1';
                    }
                    else {
                        bi[i] = '0';
                    }
                }

                // get final output in decimal
                output = stoi(bi, 0, 2);
            }

        // if number of elements size is 3
        }
        else if (element.size() == 3) {

            // AND operation
            if (operation == "A") {

                output = (stoi(element[1]) & stoi(element[2]));

            // OR operation
            }
            else if (operation == "O") {

                output = (stoi(element[1]) | stoi(element[2]));

            // XOR operation
            }
            else if (operation == "X") {

                output = (stoi(element[1]) ^ stoi(element[2]));


            // Shiftbit operation
            }
            else {

                // get decimal number and total number of bit to shift
                int decimal = stoi(element[2]);
                int shiftCount = stoi(element[1]);

                // Right Shift
                if (operation == "RS") {

                    output = (decimal >> shiftCount);

                // Left Shift
                }
                else if (operation == "LS") {

                    output = (decimal << shiftCount);

                // Roundshift operation
                }
                else {

                    // convert decimal to binary
                    string binary = toBinary(decimal);

                    // Right circle shift
                    if (operation == "RC") {

                        // copy a group rightmost bit that have size equal to number of bit need to be shifted
                        string shiftBit = binary.substr(binary.size() - shiftCount, shiftCount);

                        // eliminated the coppied bit in the original binary string
                        binary.erase(binary.size() - shiftCount, shiftCount);

                        // add copied bit to the left of the new binary string
                        binary = shiftBit + binary;

                        // convert to decimal
                        output = stoi(binary, 0, 2);

                    // left circle shift
                    }
                    else if (operation == "LC") {

                        // copy a group leftmost bit that have size equal to number of bit need to be shifted
                        string shiftBit = binary.substr(0, shiftCount);

                        // eliminated the coppied bit in the original binary string
                        binary.erase(0, shiftCount);

                        // add coppied bit to the right of the new binary string
                        binary = binary + shiftBit;

                        // convert to decimal
                        output = stoi(binary, 0, 2);

                    }
                }
            }
        }

        // check output
        // if output still unmodified, return invalid command message
        if (output == -1) {

            cout << "\nInvalid Commad" << endl;

        }
        else {

            cout << "\nThe base ten value is: " << output << endl;

        }

        // run again decision
        cout << "\nRun Again (Y/N): ";
        cin >> runAgain;
        cin.ignore();

    } while (runAgain == 'y' || runAgain == 'Y');
}



