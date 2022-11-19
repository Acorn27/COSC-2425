/*
Author: Mai Tran
Course: COSC 2425
Program Set 2-1
Reference:
	How to delete vector element by using index: https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// remove white space element
void rmSpace(vector<string>& expression) {

	for (unsigned i = 0; i < expression.size(); i++) {

		if (expression[i] == " ") {

			expression.erase(expression.begin() + i);

		}

	}

}

// display simplifier expression
void display(vector<string>& expression) {

	rmSpace(expression);

	cout << "\nSimplified expression: ";

	for (unsigned i = 0; i < expression.size(); i++) {

		if (expression[i] == "+" || expression[i] == "*") {

			cout << " " << expression[i] << " ";
			continue;

		}

		cout << expression[i];

	}

	cout << endl;

}

// get operators, operands, and parathesis into vector in correct order
bool fillVector(vector<string>& expression, string& input) {

	int operands = 0;
	int operators = 0;
	double parathesis = 0;

	for (unsigned i = 0; i < input.size(); i++) {

		char temp1 = input[i];

		if (isspace(input[i])) {
			continue;
		}


		else if (temp1 != '+' && temp1 != '*' && temp1 != '~' && temp1 != 'A' && temp1 != 'B' && temp1 != '(' && temp1 != ')' && temp1 != '1' && temp1 != '0') {

			cout << "\nValid Input characters contains A, B, +, *, ~, (, ), 1 and 0 only\n";
			return (false);

		}
		else {

			if (temp1 == 'A' || temp1 == 'B' || temp1 == '1' || temp1 == '0') {

				operands++;

			}
			else if (temp1 == '(' || temp1 == ')') {

				parathesis += 0.5;

			}
			else {

				operators++;

			}

			if (input[i] == '~' && isalpha(input[i + 1])) {

				string couple = string(1, input[i + 1]);
				couple = "~" + couple;
				expression.push_back(couple);
				i++;

			}
			else {

				expression.push_back(string(1, temp1));

			}

		}

	}

	if (operands > 3 || operators > 3 || parathesis > 1) {

		cout << operands << " " << operators << " " << parathesis << endl;
		cout << "\nPlease enter the expression contains at most 3 operands, 3 operators and one set of parentheses\n";

		return (false);

	}

	return (true);

}

// check if vector element is an operand
bool isOperand(const string test) {

	if ((test.length() == 1 && isalpha(test[0])) || (test.length() > 1 && isalpha(test[1]))) {

		return (true);

	}
	else {
		return (false);
	}

}

// apply demorgan law
bool demorgan(vector<string>& expression) {

	if (expression.size() < 6) { return (false); };

	for (int i = 0; i <= 2; i++) {

		// just ignore boundary check for now
		if (expression[i] == "~" && expression[i + 1] == "(" && isOperand(expression[i + 2]) && expression[i + 3] == "+" && isOperand(expression[i + 4]) && expression[i + 5] == ")") {

			expression[i + 1] = " ";
			expression[i + 3] = "*";
			expression[i + 5] = " ";
			expression.insert(expression.begin() + i + 4, "~");

			rmSpace(expression);
			return (true);
		}
		else if (expression[i] == "~" && expression[i + 1] == "(" && isOperand(expression[i + 2]) && expression[i + 3] == "*" && isOperand(expression[i + 4]) && expression[i + 5] == ")") {

			expression[i + 1] = " ";
			expression[i + 3] = "+";
			expression[i + 5] = " ";
			expression.insert(expression.begin() + i + 4, "~");

			rmSpace(expression);
			return (true);
		}

	}

	return false;

}

//double negation law
bool doubleNeg(vector<string>& expression) {

	bool flag = false;

	for (unsigned i = 0; i < expression.size() - 1; i++) {

		if (expression[i] == "~" && expression[i + 1].length() == 2) {


			expression[i] = ' ';
			expression[i + 1][0] = ' ';

			flag = true;
		}

	}

	rmSpace(expression);

	return (flag);

}

// distributive law for only 2 variable, which contains only 2 scenraios
// A*(B+A) = AB + A = A
// B*(A + B) = AB + B = B
bool distrLaw(vector<string>& expression) {

	bool flag = false;

	if (expression.size() < 7) { return (false); };

	for (int i = 0; i <= 1; i++) {

		if (isOperand(expression[i]) && expression[i + 1] == "*" && expression[i + 2] == "(" && isOperand(expression[i + 3]) && expression[i + 4] == "+" && isOperand(expression[i + 5]) && expression[i + 6] == ")") {

			expression[i + 1] = "*";
			expression[i + 2] = expression[i + 3];
			expression[i + 3] = "+";
			expression[i + 4] = expression[i];
			expression[i + 6] = expression[i + 5];
			expression[i + 5] = "*";

			flag = true;

		}
	}

	rmSpace(expression);

	return (flag);

}

// absorptive Law, need swap position
bool absorLaw(vector<string>& expression) {

	bool flag = false;

	if (expression.size() < 4) {

		return false;

	}

	for (unsigned i = 0; i <= expression.size() - 4; i++) {

		// eliminate false apply of distributive law
		// A * A + A * B != A *( A  + A * B) == A *A
		if (i != 0 && i != expression.size() - 4) {

			if (expression[i - 1] == "*" || expression[i + 5] == "*") {

				continue;

			}
		}

		if ((expression[i] == "A" || expression[i] == "B") && expression[i + 1] == "+" &&
			isOperand(expression[i + 2]) && expression[i + 3] == "*" && (expression[i + 4] == "A" || expression[i + 4] == "B")) {

			// A + A*B = A
			if (expression[i + 2].size() == 1 && expression[i + 2] != expression[i + 4]) {

				for (unsigned j = i + 1; j <= i + 4; j++) {
					expression[j] = " ";
				}

				flag = true;
				//debug
				flag = true;


			} // A + ~A * B = A + B. This function alone can work with A + B * ~A
			else if (expression[i + 2].size() == 2 && expression[i + 2] != expression[i + 4]) {

				// only works with the same variable with ~. Example: A + ~A * B
				if (expression[i][0] == expression[i + 2][1]) {

					expression[i + 2] = expression[i + 4];

					for (unsigned j = i + 3; j <= i + 4; j++) {

						expression[j] = " ";
					}

					//debug
					flag = true;


				}

			}

		}

	}

	rmSpace(expression);
	return (flag);


}

// idempotent law
bool idempLaw(vector<string>& expression) {

	if (expression.size() < 3) {
		return false;
	}

	bool flag = false;

	for (unsigned i = 0; i < expression.size() - 3; i++) {

		// general condition for idempotent law
		if (isOperand(expression[i]) && isOperand(expression[i + 2]) && expression[i] == expression[i + 2]) {

			// A * A scenario
			if (expression[i + 1] == "*") {

				expression[i + 1] = " ";
				expression[i + 2] = " ";
				flag = true;

			}//A + A scenario
			else if (expression[i + 1] == "+") {

				if (i == 0 && i == expression.size() - 3) {

					expression[i + 1] = " ";
					expression[i + 2] = " ";
					flag = true;
					// only apply idempotent when there is no * at the begining and the end
				}
				else if (expression[i - 1] != "*" && expression[i + 3] != "*") {

					expression[i + 1] = " ";
					expression[i + 2] = " ";
					flag = true;

				}

			}

		}

	}

	rmSpace(expression);
	return (flag);

}

// complement law. it is a modified coppied of indeompotent law
bool complementLaw(vector<string>& expression) {

	if (expression.size() < 3) {
		return false;
	}

	bool flag = false;

	for (unsigned i = 0; i <= expression.size() - 3; i++) {

		if (isOperand(expression[i]) && isOperand(expression[i + 2]) && ((expression[i + 2].size() == 2 && expression[i + 2][1] == expression[i][0]) ||
			(expression[i].size() == 2 && expression[i][1] == expression[i + 2][0]))) {

			if (expression[i + 1] == "*") {

				expression[i] = "0";
				expression[i + 1] = " ";
				expression[i + 2] = " ";
				flag = true;

			}
			else if (expression[i + 1] == "+") {

				if (i == 0 && i == expression.size() - 3) {

					expression[i] = "1";
					expression[i + 1] = " ";
					expression[i + 2] = " ";
					flag = true;

				}
				else if (expression[i - 1] != "*" && expression[i + 3] != "*") {

					expression[i] = "1";
					expression[i + 1] = " ";
					expression[i + 2] = " ";
					flag = true;

				}

			}

		}

	}

	rmSpace(expression);
	return (flag);

}

bool annihilatorLaw(vector<string>& expression) {

	if (expression.size() < 3) {
		return false;
	}

	bool flag = false;

	for (unsigned i = 0; i <= expression.size() - 2; i++) {

		if ((expression[i] == "1" && expression[i + 1] == "+") || (expression[i] == "+" && expression[i + 1] == "1")) {

			expression.clear();
			expression.push_back("1");
			flag = true;
			break;

		}

		if ((expression[i] == "0" && expression[i + 1] == "*") || (expression[i] == "*" && expression[i + 1] == "0")) {

			expression.clear();
			expression.push_back("0");
			flag = true;
			break;

		}

	}

	return (flag);


}



int main() {

	string input;
	cout << "Enter a string: ";
	getline(cin, input);

	vector<string> expression;

	if (fillVector(expression, input)) {


		demorgan(expression);

		distrLaw(expression);

		doubleNeg(expression);

		absorLaw(expression);

		idempLaw(expression);

		complementLaw(expression);

		demorgan(expression);

		distrLaw(expression);

		doubleNeg(expression);

		absorLaw(expression);

		idempLaw(expression);

		complementLaw(expression);

		annihilatorLaw(expression);

		display(expression);


	}
}