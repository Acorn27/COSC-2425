/*
Author: Mai Tran
Course: COSC 2425
Program Set 1
Reference: I got idea how to convert from string subscript to int from this website:
https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// upper bound for the base of number
const int MAX_BASE = 16;

// function to return rounded output
// take 3 values as parameter: the string input, the base of number, and the number of place to be rounded
string finalValue(const string rawValue, const unsigned base, const unsigned decimalNum) {

	// hold final value
	string finalValue;

	// seperate decimal and integer part from string
	int dotPos = rawValue.find(".");
	string integerPart = rawValue.substr(0, dotPos);
	string decimalPart = rawValue.substr((dotPos + 1), rawValue.size() - dotPos);

	// if number of places to be rouded less than number of existed decimal numbers
	// don't format the output
	if (decimalPart.size() <= decimalNum) {
		
		return rawValue;

	}
	else {
		
		// hold quotient 
		double quotient;

		//convert from char to int
		long dividend = decimalPart[decimalNum] - 48;

		//calculate quotient
		quotient = dividend / double(base);
		
		// if true, increase ASCII code by one
		// assume rounding place will never be 0
		if (quotient >= 0.5) {

			decimalPart[decimalNum - 1]++;
		}
	}

	// final value is the combination of unformated integer part and formated decimal part;
	finalValue = integerPart + "." + decimalPart.substr(0, decimalNum);
	
	return finalValue;
}

int main() {

	string input;			// hold user string input
	unsigned base,			// hold base of the the number
		decimalPlace;		// hold number of decimal place to be rounded
	char runAgain = 'Y';	// run agian flag

	do {

		// prompt for value
		cout << "\nEnter the value: ";
		getline(cin, input);

		// prompt for base
		cout << "Enter the base of the number: ";
		cin >> base;
		while (base <= 0 || base > MAX_BASE) {
			cout << "Invalid input\n";
			cout << "Enter the base of the number: ";
			cin >> base;
		}

		//prompt for number of decimal place
		cout << "Number of decimal places to round: ";
		cin >> decimalPlace;

		//display result
		cout << "\nThe resulting value: " << finalValue(input, base, decimalPlace) << endl;

		// run again loop
		cout << "\nRun again (Y/N): ";
		cin >> runAgain;
		runAgain = toupper(runAgain);

		// elimiate getline error for the next iteration
		cin.ignore();

	} while (runAgain == 'Y');

	cout << "\nDone\n";
	return 0;
}
