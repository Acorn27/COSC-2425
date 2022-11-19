/*
Author: Mai Tran
Course: COSC 2425
Program Set 1
Reference:
I got the the idea to calcualte actual hard drive capacity from the website:
https://www.minitool.com/lib/hard-drive-capacity.html#:~:text=The%20hard%20drive%20capacity%20calculation,MB%2F1024%3D111.8GB.
*/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;


// structure to format input data
struct Data {

	int magnitude = 0;
	string preFix;
};

// function to separate string input into 2 part for easier to process
// take string input by user and Data structure as parameter
// return true/false depend on the validation of user input
bool formatInput(const string input, Data& d) {

	int spaceIndex;						// hold position of space " " 
	spaceIndex = input.find(" ", 0);
	
	// return true if space is found, otherwise return false 
	if (spaceIndex != string::npos) {

		// get magnitude
		string temp = input.substr(0, spaceIndex - 0);
		d.magnitude = stoi(temp);
		
		// get unit
		temp = input.substr(spaceIndex + 1, input.size() - spaceIndex);
		for (unsigned i = 0; i < temp.size(); i++) {
			temp[i] = toupper(temp[i]);
		}
		d.preFix = temp;

		return true;
	}
	else {

		return false;

	}
}

// function to calcualte and display actual size of hard drive
// take Data structure as parameter
// display actual hard drive size
void displayActualSize(const Data d) {

	const int COUNT = 7;
	string retailPrefix[COUNT] = { "KB", "MB", "GB", "TB", "PB", "EB" };
	string computerPrefix[COUNT] = { "KiB", "MiB", "GiB", "TiB", "PiB", "EiB" };


	double ratio,				// ratio of actual size (compueter size) to retail price
		   actualSize;

	// loop to find and calculate the correct ratio
	for (int i = 0; i < COUNT; i++) {

		if (d.preFix == retailPrefix[i]) {

			ratio = pow(10.0, 3 * (i + 1)) / pow(2, 10 * (i + 1));
			actualSize = d.magnitude;
			actualSize *= ratio;

			// if actual size is greater than or equal 1, keep current prefix 
			if (actualSize >= 1 || i == 0) {
				cout << "The corresponding binary drive size: " << actualSize << " " << computerPrefix[i] << endl;
			}
			// if actual size is less than 1, convert to the lower prefix
			else {
				actualSize *= 1024;
				cout << "The corresponding binary drive size: " << actualSize << " " << computerPrefix[i - 1] << endl;
			}
			cout << endl;

			// exit function prefix is found
			return;
		}

	}

	// error message if prefix is not found
	cout << d.preFix << " is not found\n";
	cout << "Please re-run program and enter the valid one\n";
}



int main() {

	string input;			// store user input
	char runAgain = 'Y';	// flag
	Data hardDrive;			// structure variable to organize user input

	do {
		cout << "Enter the hard drive size: ";
		getline(cin, input);

		// re-run do-while loop if input is invalid
		if ((formatInput(input, hardDrive)) == false) {
			cout << "Invalid input. Please re-run program\n";
			continue;
		}
		
		// format number display
		cout << setprecision(2) << fixed << showpoint;

		// calculate and display acutal size
		displayActualSize(hardDrive);
		

		// repeat loop or not ?
		cout << "Run again (Y/N): ";
		cin >> runAgain;
		runAgain = toupper(runAgain);

		// elminate getline error for next interation
		cin.ignore();

	} while (runAgain == 'Y');

	// notify and exit program
	cout << "\nDone\n";
	return 0;
}

