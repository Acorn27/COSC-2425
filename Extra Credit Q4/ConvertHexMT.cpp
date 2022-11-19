/*
Author: Mai Tran
Course: COSC 2525
Prgram: Quiz 4 - EC
Reference:
    +I got code from this website and did some modification: https://www.geeksforgeeks.org/convert-hexadecimal-value-string-ascii-value-string/
*/


// C++ program to convert hexadecimal
// string to ASCII format string
#include <iostream>
#include <string>
using namespace std;

string hexToASCII(string hex)
{
    // initialize the ASCII code string as empty.
    string ascii = "";
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        // extract two characters from hex string
        string part = hex.substr(i, 2);

        // change it into base 16 and
        // typecast as the character
        char ch = stoul(part, nullptr, 16);

        // add this char to final ASCII string
        ascii += ch;
    }
    return ascii;
}

// Driver Code
int main()
{

    string input;
    // get hexString from user
    cout << "Enter hex string: ";
    getline(cin, input);

    // display ASCII value
    cout << endl << hexToASCII(input) << endl;

    return 0;
}