/*
Author: Mai Tran
Course: COSC 2425
Program set 2-4
Reference:
    How to read from file until the end of line:
    https://stackoverflow.com/questions/21334173/read-from-file-in-c-till-end-of-line

*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// debug function to display vector
void display2D(vector<vector<string> > vtr) {

    for (unsigned i = 0; i < vtr.size(); i++) {

        cout << i + 1 << ": ";
        for (unsigned j = 0; j < vtr[i].size(); j++) {

            cout << vtr[i][j] << "--";

        }
        cout << endl;

    }

}

// determine operation
string getOperation(string output) {

    // return string
    string returnValue;

    if (output == "0001") {

        returnValue = "AND";

    }
    else if (output == "0111") {

        returnValue = "OR";

    }
    else if (output == "0110") {

        returnValue = "XOR";

    }
    else if (output == "1110") {

        returnValue = "NAND";

    }
    else if (output == "1000") {

        returnValue = "NOR";

    }
    else if (output == "1001") {

        returnValue = "XNOR";
    }

    return(returnValue);

}

// complement function for short
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}




string getOperationV2(string output) {

    // initialize score and each operation
    int score[6] = { 0, 0, 0, 0, 0, 0 };

    string operation[6] = { "AND", "OR", "XOR", "AND", "NOR", "XNOR" };

    for (unsigned i = 0; i < output.size(); i++) {


        if (output[i] == '*') {

            continue;
        }


        // first character
        if (output[0] == '0') {

            score[0]++;
            score[1]++;
            score[2]++;
            score[3] = -99;
            score[4] = -99;
            score[5] = -99;


        }
        else {

            score[0] = -99;
            score[1] = -99;
            score[2] = -99;
            score[3]++;
            score[4]++;
            score[5]++;

        }


        // second character
        if (output[1] == '0') {

            score[0]++;
            score[1] = -99;
            score[2] = -99;
            score[3] = -99;
            score[4]++;
            score[5]++;


        }
        else {

            score[0] = -99;
            score[1]++;
            score[2]++;
            score[3]++;
            score[4] = -99;
            score[5] = -99;

        }

        // third character
        if (output[2] == '0') {

            score[0]++;
            score[1] = -99;
            score[2] = -99;
            score[3] = -99;
            score[4]++;
            score[5]++;


        }
        else {

            score[0] = -99;
            score[1]++;
            score[2]++;
            score[3]++;
            score[4] = -99;
            score[5] = -99;

        }

        // last character
        if (output[3] == '0') {

            score[0] = -99;
            score[1] = -99;
            score[2]++;
            score[3]++;
            score[4]++;
            score[5] = -99;


        }
        else {

            score[0]++;
            score[1]++;
            score[2] = -99;
            score[3] = -99;
            score[4] = -99;
            score[5]++;

        }

    }

    // find the best suit operation
    int maxIndex = 0;
    while (score[maxIndex] < 0) {
        maxIndex++;
    }

    for (int index = maxIndex + 1; index < 6; index++) {

        if (score[maxIndex] < score[index]) {

            maxIndex = index;

        }

    }
    return(operation[maxIndex]);

}



int main() {

    // hold file name
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    cout << endl;


    // file stream object
    ifstream inputFile;
    inputFile.open(fileName);

    if (!(inputFile)) {

        cout << "Error Opening File\n";
    }
    else {

        // hold number of value in file
        int varNum;
        inputFile >> varNum;

        // temporary string to hold each line data
        string temp;

        // skip the first line
        getline(inputFile, temp);

        // 2d vector to hold input
        vector<vector<string> > inputV;

        while (getline(inputFile, temp)) {

            istringstream ss(temp);
            string num;
            vector<string> tempV;

            // get data for inner vector
            while (ss >> num) {
                tempV.push_back(num);
            }

            // push inner vector into outter vector
            inputV.push_back(tempV);

        }

        // process each value
        for (int i = 0; i < varNum; i++) {

            // 2d vector to hold table, each vector hold data for each column
            vector<vector<string> > table;

            // initialize first columns, which hold data for a
            vector<string> tempV = { "0", "0" , "1", "1" };
            table.push_back(tempV);

            // initialize second columns, which hold data for b
            tempV = { "0", "1", "0", "1" };
            table.push_back(tempV);

            // initialize the remaining of the columns

            for (int j = 0; j < stoi(inputV[i][1]); j++) {

                vector<string> tempV;
                tempV.push_back(string(1, inputV[i][2][j]));
                tempV.push_back(string(1, inputV[i][3][j]));
                tempV.push_back(string(1, inputV[i][4][j]));
                tempV.push_back(string(1, inputV[i][5][j]));
                table.push_back(tempV);

            }


            // hold data for operands
            vector<string> operands;

            operands.push_back("A");
            operands.push_back("B");

            // determine operation for third column
            string output;
            for (int i = 0; i < 4; i++) {

                output += table[2][i];

            }

            string temp3 = " ";
            temp3 = "(A " + getOperationV2(output) + " B)";
            operands.push_back(temp3);




            // table index
            int tableIndex = 3;

            // determine the remaining operation
            for (unsigned j = 7; j < inputV[i].size(); j++) {

                int value1 = inputV[i][j][0] - '0';
                int value2 = inputV[i][j][1] - '0';

                output = "****";

                for (int k = 0; k < 4; k++) {

                    if (table[value1 - 1][k] == "0" && table[value2 - 1][k] == "0") {

                        output[0] = table[tableIndex][k][0];

                    }
                    else if (table[value1 - 1][k] == "0" && table[value2 - 1][k] == "1") {

                        output[1] = table[tableIndex][k][0];

                    }
                    else if (table[value1 - 1][k] == "1" && table[value2 - 1][k] == "0") {

                        output[2] = table[tableIndex][k][0];

                    }
                    else if (table[value1 - 1][k] == "1" && table[value2 - 1][k] == "1") {

                        output[3] = table[tableIndex][k][0];

                    }

                }


                string temp4 = " ";
                temp4 = "(" + operands[value1 - 1] + " " + getOperationV2(output) + " " + operands[value2 - 1] + ")";
                operands.push_back(temp4);
                tableIndex++;
            }

            cout << "Set " << i + 1 << ": " << operands[operands.size() - 1] << endl;


        }


    }
}






