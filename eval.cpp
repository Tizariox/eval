/*
Arithmetic Expression Evaluator -- Alan Zhong

This C++ program parses an input string and evaluates the arithmetic expression that it contains according to the order
of operations; this is similar to an eval() function in other programming languages. However, this program only accepts
integer inputs and doesn't support division or exponentiation. 

It works by descending down the order of operations––it finds all parentheses from the innermost to the outermost and then finds
all the products in the parentheses, evaluates them, and then find the addition and subtraction, and evaluates them. This will
ensure that all parentheses are calculated before products, which are calculated before addition and subtraction. 

Syntax:
+ for addition
- for subtraction
* for multiplication
() for parentheses
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define MOD 1000000007
#define nl endl
#define pub push_back
#define pob pop_back

string evalPart(string str, int i, char operation1, char operation2) { // for sweeping through the string and evaluating all 2-part expressions containing a certain operation (Ex: 52*7, 3+41, 58-3, etc.)	
    for (int j = i + 1; j < str.length(); j++) {
		if (str[j] == ')') { // stopping point; if the character we're looking at is the end of the parentheses then we stop and repeat for the next parentheses
			return str;
		} else if (j != str.length() - 1 && str[j] == '+' && str[j + 1] == '-') { // the program can't interpret adding or subtracting a negative number																	// statements are just here to replace +- with - and -- with +
			str = str.substr(0, j) + "-" + str.substr(j + 2, str.length() - j - 2);
			j--; // pushing j back to account for the +- being turned into -
		} else if (j != str.length() - 1 && str[j] == '-' && str[j + 1] == '-') {
			str = str.substr(0, j) + "+" + str.substr(j + 2, str.length() - j - 2);
			j--; // pushing j back to account for the -- being turned into +
		} else if (str[j] == operation1) { // if the character we're looking at is the first operation, we find the numbers to the left and right of the operation and evaluate the result based on hte operation. 
			// variables used to keep track of both numbers, as well as their lengths in the string (important later on for replacing the numbers with their result)
			int leftNum = 0;
            int leftNumSize = 0;
            int rightNum = 0;
            int rightNumSize = 0;
			// finding the number to the left of the operation
            for (int k = j - 1; k > 0; k--) {
                if (!isdigit(str[k])) {
			if (k == i + 1) { // if the left number is negative (this only happens when it's right next to the left parentheses because we take care of +- and --)
				leftNum *= -1;
				leftNumSize++;
			}
			break;
                } else {
					// constructing the number, digit by digit
                    leftNum += stoi(string(1, str[k])) * pow(10, j - 1 - k);
                    leftNumSize++;
                }
            }
			// finding the length of the number to the right of the operation
			bool negativeNum = false;
            for (int k = j + 1; k < str.length(); k++) {
                if (!isdigit(str[k])) {
					if (k == j + 1) { // if the right number is negative (this only happens when the operation is '*' because we take care of +- and --), we have to have a special case
						negativeNum = true;
						rightNumSize++;
					} else {
						break;
					}
                } else {
                    rightNumSize++;
                }
            }
			// constructing the number, digit by digit
            for (int k = j + 1; k < j + 1 + rightNumSize; k++) {
				if (negativeNum && k == j + 1) { // if the right number is negative we continue the first time because it's just a '-'
					continue;
				}
                rightNum += stoi(string(1, str[k])) * pow(10, j + rightNumSize - k);
            }
			if (negativeNum) { // making the number negative
				rightNum *= -1;
			}
			// finding the result based on both numbers and the operation
			int result = (operation1 == '*') ? leftNum*rightNum : ((operation1 == '+') ? leftNum + rightNum : leftNum - rightNum);
            str = str.substr(0, j - leftNumSize) + to_string(result) + str.substr(j + rightNumSize + 1, str.length() - j - rightNumSize - 1);
            j -= leftNumSize; // reset j after removing left number because the
                              // left number being removed shifts the original j
                              // to the left
		} else if (str[j] == operation2) { // doing the same thing, but for the second operation: this is necessary so that we can evaluate + and - at the same time
			int leftNum = 0;
            int leftNumSize = 0;
            int rightNum = 0;
            int rightNumSize = 0;
            for (int k = j - 1; k > 0; k--) {
                if (!isdigit(str[k])) {
			if (k == i + 1) {
			leftNum *= -1;
			leftNumSize++;
			}
                break;
                } else {
                    leftNum += stoi(string(1, str[k])) * pow(10, j - 1 - k);
                    leftNumSize++;
                }
            }
            for (int k = j + 1; k < str.length(); k++) {
                if (!isdigit(str[k])) {
                    break;
                } else {
                    rightNumSize++;
                }
            }
            for (int k = j + 1; k < j + 1 + rightNumSize; k++) {
                rightNum += stoi(string(1, str[k])) * pow(10, j + rightNumSize - k);
            }
            int result = (operation2 == '*') ? leftNum * rightNum : ((operation2 == '+') ? leftNum + rightNum : leftNum - rightNum);
            str = str.substr(0, j - leftNumSize) + to_string(result) + str.substr(j + rightNumSize + 1, str.length() - j - rightNumSize - 1);
            j -= leftNumSize; // reset j after removing left number because the
                              // left number being removed shifts the original j
                              // to the left
		}
	}
	return str;
}

int eval(string str) { // eval function; this is the code that will evaluate the string
	// get rid of all whitespace
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str = "(" + str + ")"; // makes it so that we don't have to do anything extra at the end; the string will just turn into the end result because everything is surrounded in parentheses
	// following order of operations, we evaluate each pair of parentheses
	for (int i = str.length() - 1; i >= 0; i--) {
		if (str[i] == '(') {
			// evaluate all 2-part expressions inside the parentheses, going from * then to + and - (a 2 part expression is just a (operation) b --> ex: 4*7 or 12-5)
			str = evalPart(str, i, '*', '*');
            str = evalPart(str, i, '+', '-');
			// finding where the parentheses stops; then deleting the parentheses. Note that at this point, the expression inside the parentheses has already been evaluated using evalPart, so it's just a number now. 
            for (int j = i + 1; j < str.length(); j++) {
				if (str[j] == ')') {
					str = str.substr(0, i) + str.substr(i + 1, j - i - 1) + str.substr(j + 1, str.length() - j); // getting rid of parentheses
					break;
				}
			}
		}
	}
	return stoi(str);
}

int main() {
	// driving code, inputs a number, evaluates it, and prints the simplified form
	string toEval = "";
	cout << "What string do you want to evaluate? " << nl;
	cin >> toEval;
	cout << "The answer is " << eval(toEval) << "." << nl; 
}
