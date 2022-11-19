/*
Author: Mai Tran
Course: COSC 2425
Program Set 2-2
Rreference: 
	I got the algorithm to convert form FSA to RE from this website:
	https://rpruim.github.io/m252/S19/from-class/models-of-computation/dfanfa-to-regular-expression.html#algorithm-for-converting-dfanfa-to-regular-expression
	I test my code using the simulation from this website:
	https://ivanzuzak.info/noam/webapps/fsm2regex/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

	//get number of state
	int stateNum;
	cout << "Enter the number of FSA state: ";
	cin >> stateNum;

	// get data for table
	cin.ignore();
	string tableData;
	cout << "Enter the table data: ";
	getline(cin, tableData);

	// hold data for each state
	vector<string> stateData;
	int count = 0;

	// get data
	for (unsigned i = 0; i < tableData.size() && count < stateNum; i+= 3) {

		string temp = tableData.substr(i, 2);
		stateData.push_back(temp);
		count++;

	}

	string regex;
	// I don't know what Im doing
	for (unsigned i = 0; i < stateData.size(); i++) {

		// convert int to char
		char nextState = i + 2 + '0';
		char currentState = i + 1 +'0';

		string temp = "";

		if (stateData[i][0] == stateData[i][1] && stateData[i][0] != '0') {

			regex += "(a+b)";
			continue;

		}

		for (int j = 0; j < 2; j++) {

			if (stateData[i][j] == nextState) {

				if (j == 0) {
					temp += "a";
				}
				else if (j == 1) {
					temp += "b";
				}

			} else if (stateData[i][j] == currentState) {

				if (j == 0) {
					temp += "a*";
				}
				else if (j == 1) {
					temp += "b*";
				}
			}

		}
		
		if (temp.size() == 3 && temp[2] == '*') {

			regex.append(temp, 1, 2);
			regex += temp[0];

		}
		else {

			regex += temp;
		}

	}

	// display output
	cout << "\nEquivalent regular expression: " << regex << endl;



}