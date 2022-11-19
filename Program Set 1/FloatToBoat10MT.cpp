/*
Author: Mai Tran
Course: COSC 2425
Program set 1
Reference: None
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// function to read data from a file entered by user
// take file name and a string vector as parameters
// then write data into an existed vector
// return true if file opened successfully
// otherwise return false
bool readFile(const string fileName, vector<string>& v) {

	ifstream inputFile;
	inputFile.open(fileName);

	// flag, set false as default
	bool successOpen = false;

	// hold number of data sets
	int count;

	// process if file opened successfully
	if (inputFile) {

		// get number of data sets
		inputFile >> count;

		// only read the fixed number of data sets
		for (int i = 0; i < count; i++) {

			string temp;
			inputFile >> temp;
			v.push_back(temp);

		}

		// set status to true since file is successfully opened 
		successOpen = true;

	}

	inputFile.close();

	return successOpen;

}

// a function that convert from floating to base number
// take string as parameter
// display formatted string of converted number
void toBase(const string str) {

	// get sign
	string sign = str.substr(0, 1);
	string signPart = "";
	if (sign == "1") {

		signPart = "-";

	}

	// get exponent
	string exponent = str.substr(1, 11);
	int exponentTotal = 0;
	// calculate exponent number
	for (unsigned i = 0; i < exponent.length(); i++) {

		if (exponent[i] == '1') {

			exponentTotal += static_cast<int>(pow(2, exponent.length() - i - 1));

		}
	}
	// calculate exponent number which equal exponent total - 1023
	int exponentNumber = exponentTotal - 1023;

	//get mantissa
	string mantissa = str.substr(12, str.length() - 12);
	double mantissaTotal = 0;
	//calculate mantissa total
	for (unsigned i = 0; i <= mantissa.length(); i++) {

		if (mantissa[i] == '1') {

			mantissaTotal += 1 / pow(2, i + 1);

		}
	}
	// calculate mantissa number
	double mantissaNumber = mantissaTotal + 1;

	// calculate final value
	double decimalNumber = mantissaNumber * pow(2, exponentNumber);

	// format numeric output
	cout << setprecision(2) << fixed << showpoint;

	// display final value
	cout << signPart << decimalNumber;

}


int main() {

	// hold file's name entered my user
	string fileName;

	// vector variable to hold n sets of value
	vector<string> floating;

	// promt for input fileName
	cout << "\nEnter the file name: ";
	cin >> fileName;
	cout << endl;

	// read data from file into vector
	if (readFile(fileName, floating)) {

		// display converted base number
		for (unsigned i = 0; i < floating.size(); i++) {

			cout << "Set " << i + 1 << ": ";
			toBase(floating[i]);
			cout << endl;

		}

	}
	else {
		cout << "\nError opening " << fileName << endl;
	}

}