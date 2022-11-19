/*
Author: Mai Tran
Course: COSC 2425
Program set 2-3
Reference: i got the code form chegg study and did some modifications
*/

#include <iostream>
#include <string>
using namespace std;

//this function converts the hexadecimal to binary and returns the same
string HexToBin(string hexdec)
{
	// hold converted binary value
	string binary;

	// string element index
	long int i = 0;

	// step through hexdex string and convert it to binary
	while (hexdec[i]) {

		switch (hexdec[i]) {
		case '0':
			binary += "000";
			break;
		case '1':
			binary += "001";
			break;
		case '2':
			binary += "010";
			break;
		case '3':
			binary += "011";
			break;
		case '4':
			binary += "100";
			break;
		case '5':
			binary += "101";
			break;
		case '6':
			binary += "110";
			break;
		case '7':
			binary += "111";
			break;
		case '8':
			binary += "1000";
			break;
		case '9':
			binary += "1001";
			break;
		case 'A':
		case 'a':
			binary += "1010";
			break;
		case 'B':
		case 'b':
			binary += "1011";
			break;
		case 'C':
		case 'c':
			binary += "1100";
			break;
		case 'D':
		case 'd':
			binary += "1101";
			break;
		case 'E':
		case 'e':
			binary += "1110";
			break;
		case 'F':
		case 'f':
			binary += "1111";
			break;
		default:
			cout << "\nInvalid hexadecimal digit " << hexdec[i];
		}
		i++;
	}

	// return binary string
	return binary;
}

// Returns XOR of 'a' and 'b'
string xor1(string a, string b)
{

	// Initialize result
	string result = "";

	int n = b.length();

	//if the bits are same, then result is 0 else result is 1
	for (int i = 1; i < n; i++)
	{
		if (a[i] == b[i])
			result += "0";
		else
			result += "1";
	}
	return result;
}

// Performs Modulo-2 division
string mod2div(string divident, string divisor)
{

	// Number of bits to be XORed at a time.
	int pick = divisor.length();

	// taking the divident to appropriate length to do XOR operation
	string tmp = divident.substr(0, pick);

	int n = divident.length();

	while (pick < n)
	{
		if (tmp[0] == '1')

			// Replace the divident by the result of XOR and pull 1 bit down
			tmp = xor1(divisor, tmp) + divident[pick];
		else

			// If leftmost bit is '0' the step cannot use the regular divisor; we need to use an all-0s divisor.
			tmp = xor1(std::string(pick, '0'), tmp) +
			divident[pick];

		// Increment pick to move to further bits
		pick += 1;
	}

	// For the last n bits, we have to carry it out normally as increased value of pick will cause Index Out of Bounds error.
	if (tmp[0] == '1')
		tmp = xor1(divisor, tmp);
	else
		tmp = xor1(std::string(pick, '0'), tmp);

	return tmp;
}

// Driver code
int main()
{
	// hold data and key in hex and binary
	string datahex, data, keyhex, key;

	// gey data and key in hex
	cout << "Enter two hex values separated by a space: ";
	cin >> datahex >> keyhex;

	// convert data from hex to binary
	data = HexToBin(datahex);

	// convert key from hex to binary
	key = HexToBin(keyhex);


	string appended_data = (data + string(key.length() - 1, '0'));

	string crc = mod2div(appended_data, key);

	cout << "\nCRC Checksum : " << crc << "\n";

	return 0;

}