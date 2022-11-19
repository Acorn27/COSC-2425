/*
Author: Mai Tran
Course: COSC 2425
Extra Credit Q1
Reference: I use the the algorithm convert decimal to binary from the following website:
https://www.javatpoint.com/cpp-program-to-convert-decimal-to-binary
*/

#include <iostream>
#include <cmath>
using namespace std;


// a function convert individual integer to binary
// then calculate number of times 1's appeared
// binary doesn't have to be in the correct orientation
// take an integer as constant parameter because
// we don't want to alter loop's interation 
int calcOne(const int decimal) {

	// variable to hold number of times digit 1 appear
	int oneCalc = 0;

	// tempory variable to hold value of decimal so we don't accidentaly
	// modify the iteration of loop in main when using this function
	int temp = decimal;

	// convert deciaml to binary
	for (int i = 0; temp > 0; i++) {

		int binary = (temp % 2);
		if (binary == 1) {
			
			// if binary digit equal 1, increase count variable by one
			oneCalc++;

		}

		temp = temp / 2 ;
	}

	return (oneCalc);

}

// a function to get positive number that sastified requirement
// return validated number
int getNumber() {

	// get positive number and input validation
	int decimal;
	do {

		cout << "Enter a number (50 or less): ";
		// get integer only
		if (!(cin >> decimal)) {
			cout << "Please enter numbers only\n";
			cin.clear();
			cin.ignore(1000, '\n');
		// range validation
		} else if (decimal < 1 || decimal > 50) {

			cout << "Please enter numbers in range of 1-50 only\n";

		} else {
			// break through loop and function
			return (decimal);
		}

	} while (true);

}

int main() {

	// an integer variable to hold a number 
	int decimal;			

	// get number from user and input validation
	decimal = getNumber();

	// variabe to hold end point
	int end = static_cast<int>(pow(2, decimal));

	// varibale to hold number of time digit 1 has appear
	long total = 0;

	// loop running from 1 to 2^k
	// calc number of time digit 1 has appeared in each number
	// and add to total;
	for (int i = 1; i <= end; i++) {

		total += calcOne(i);

	}

	//display number of times digit 1 has appeared
	cout << total << " ones appear " << endl;

	// end program
	return 0;

}