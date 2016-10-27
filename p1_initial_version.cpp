#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <string>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

using namespace std;
unordered_map<string, double> varMap;

/*parsing string with multiple delimiters
for each character, check if it is operator(call respective function)/number(int&dot)/variable(all characters && not reserved word let && not constants)

*/
/*error handling
1) divide by 0, when poping a /, check if the second operand is 0
2) while parsing the string, if it is a variable, check map to see if it is defined
*/

vector<string> parseString(string input) {
	stringstream strStream(input);
	vector<string> tokenVector;
	string line;
	string subString;
	while(getline(strStream, line)) {
	//while(getline(input, line)) {
		int start = 0;
		int found = 0;

		//while finding any of the characters
		while((found = line.find_first_of("+-*/^=()", start)) != string::npos) {

			//if the first character is target, just push it into vector
			if(found == start) {
				subString = line.substr(start, 1);
				tokenVector.push_back(subString);
			}

			//otherwise, get the substring and remove whitespace(s) and push back operand and the operator into vector
			else if(found > start) {
				subString = line.substr(start, found - start);
				//string::iterator end = std::remove(subString.begin(), subString.end(), ' ');
				subString.erase(std::remove(subString.begin(), subString.end(), ' '), subString.end());
				tokenVector.push_back(subString);
				tokenVector.push_back(line.substr(found, 1));
			}
			start = found + 1;
		}

		//handle the case when none of the characters is found after the end of line
		subString = line.substr(start, line.length() - start);
		//string::iterator end = remove(subString.begin(), subString.end(), ' ');
        subString.erase(std::remove(subString.begin(), subString.end(), ' '), subString.end());
		tokenVector.push_back(subString);
	}
	return tokenVector;
}


int precedence(string& op) {
	if(op == "=") {
		return 1;
	}
	if(op == "+" || op == "-") {
		return 2;
	}
	else if(op == "*" || op == "/") {
		return 3;
	}
	else if(op == "^") {
		return 4;
	}
    else if(op == "(") {
		return 5;
	}
	return -1;
}

//check if a token is a function
bool isFunction(string& token) {
	return (token == "sin" || token == "cos" || token == "log");
}

//check if a token is an operator
bool isOperator(string& token) {
 return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

//check if a token is an operand
bool isOperand(string& token) {
	//return (isdigit(token.at(0)) || varMap.find(token) != varMap.end());
    return (isdigit(token.at(0)) || isalpha(token.at(0)));
}

//implementing shunting yard algorithm to transform infix to postfix
queue<string> infixToPostfix(vector<string> tokens) {
	stack<string> operatorStack;
	queue<string> operandQueue;
    cout << "In infixToPostfix function\n";
    for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        cout << *it << " " << "\n";
    }
    cout <<  "\n";
	//push the tokens onto operatorStack and operandQueue accordingly
	//for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
	vector<string>::iterator it = tokens.begin();
	while(it >= tokens.end()) {
		if(isOperand(*it)) {
			operandQueue.push(*it);
			cout << "pushing operand " <<*it << " onto queue\n";
		}
		else if(*it == "(") {
			operatorStack.push(*it);
			cout << "Pushing operator " <<*it << " onto stack\n";
		}
		else if(*it == ")") {
			while(!operatorStack.empty() && operatorStack.top()!= "(") {
				operandQueue.push(operatorStack.top());
                cout << "Poping operator " << operatorStack.top() << " from stack to queue\n";
				operatorStack.pop();
			}

			//pop left parenthese off stack and discard it
			operatorStack.pop();
			cout << "Poping ( off operatorStack\n";
		}
		//else if(isOperator(*it)) {
		else {
			if(operatorStack.empty() || operatorStack.top() == "(") {
			//if(operatorStack.empty() || operatorStack.top() == "(" || isFunction(*it)) {
				operatorStack.push(*it);
			cout << "pushing operator " <<*it << " onto stack\n";
			}
			else {
				while(!operatorStack.empty() && operatorStack.top() != "(" && precedence(*it) <= precedence(operatorStack.top())) {
						operandQueue.push(operatorStack.top());
                        cout << "Pushing operators " << operatorStack.top() << " from stack to queue\n";
						operatorStack.pop();
				}
                opertorStack.push(*it);
                cout << "Pushing operator " << *it << " onto stack\n";
			}
		}
        //cout << "Before " << *it << endl;
        it++;
        //cout << "After " << *it << endl;
	}

	cout << "Poping elements from stack to queue\n";
	//pop the operatorStack and add them to the end of operandQueue until the stack is empty
	while(!operatorStack.empty()) {
		operandQueue.push(operatorStack.top());
		operatorStack.pop();
		cout << "Poping one element from stack to queue\n";
	}
    cout << "The operator stack is empty now!\n";
	return operandQueue;
}



//calculate one step of calculation
double calcResult(double op1, double op2, string& opt) {
	double result;
	if(opt == "+") {
        cout << "Plus operation in calcResult function\n";
        cout << "The operands are " << op1 << " and " << op2 << "\n";
		result = op1 + op2;
	}
	else if(opt == "-") {
		result = op1 - op2;
	}
	else if(opt == "*") {
		result = op1 * op2;
	}
	else if(opt == "/") {
		result = op1 / op2;
	}
	else if(opt == "^") {
		result = pow(op1, op2);
	}
	//any other operators?????
	return result;
}

//calculate the function
double calcFunct(string& op1, string& opt) {

}

/*//convert string to double
double stringToNumber (string& token) {
	stringstream ss(token);
	double result;
	cout << "In stringToNumber function\n";
	return ss >> result ? result : 0;
}*/

/*take a vector of string as input, call infixToPostfix function to get a queue of tokens
  then push the returned queue to a stack and use the stack to evaluate the expression
*/
double evaluateExpression(vector<string> expression) {
    cout << "In evaluateExpression function\n";
	queue<string> input;
	stack<double> stack;
	double result;

    for(vector<string>::iterator it = expression.begin(); it != expression.end(); it++) {
        cout << *it << " ";
    }
    cout <<"\n";

	input = infixToPostfix(expression);
	cout << "After calling infixToPostfix function\n";


	//using a stack to evaluate the input queue, convert operands from queue to double
	while(!input.empty()) {
		string token = input.front();
		double op1;
		double op2;

		//if the front of queue is an operand, push it onto stack, otherwise pop two operands from stack and do calculation

		if(isOperand(token)) {
			//stack.push(stringToNumber(token));
			stack.push(atof(token.c_str()));
			cout << "After stringToNumber function, pushing operand " << token << " onto stack\n";
			input.pop();
		}
		//else if(isOperator(token)) {
		else {
			op2 = stack.top();
			cout << "operand op2 is " << op2 << "\n";
			stack.pop();
			op1 = stack.top();
			cout << "operand op1 is " << op1 << "\n";
			stack.pop();
			input.pop();
			result = calcResult(op1, op2, token);
			cout << "In evaluateExpression function, the result is " << result << "\n";
			stack.push(result);
		}/*
		else if(isFunction(token)) {
			op1 = stack.pop();
			opt = input.pop();
			result = calcFunct(op1, opt);
			stack.push(result);
		}*/
	}
	return result;
}

int main() {
	vector<string> parsedString;
	string input;
	getline(cin, input);

    /*parsedString = parseString(input);
    cout << "string has been parsed successfully\n";
    for(vector<string>::iterator it = parsedString.begin(); it != parsedString.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";*/

    //while char taken from input is not whitespace, move to next char
    //not efficient!!!!!!!!
    //while(input.c_str().at[0] != ' ' ) {
        //input
    //}

    //if the first string is let and followed by at least a space
    if(input.substr(0,3) == "let"&& input.substr(0,4)== " ") {
            input.erase(0, 4);
		}



	//accept input as long as it is not "quit"
	while(input != "quit") {
		parsedString = parseString(input);


		cout << "string has been parsed successfully\n";
		for(vector<string>::iterator it = parsedString.begin(); it != parsedString.end(); it++) {
            cout << *it << " ";
		}
		cout << "\n";

		string var;
		double result;

		//if the first vector object is let, then this is an assignment
		if(!parsedString.empty() && parsedString.at(0) == "let") {
            /*cout << "string starting with let, this is before shrinking\n";
            for(vector<string>::iterator it = parsedString.begin(); it != parsedString.end(); it++) {
                cout << *it << " ";
            }*/

			var = parsedString.at(1);
			parsedString.erase(parsedString.begin(), parsedString.begin()+3);
            /*cout << "string starting with let, after shrinking\n";
            for(vector<string>::iterator it = parsedString.begin(); it != parsedString.end(); it++) {
                cout << *it << " ";
            }*/
			//evaluate the expression and assign value to variable and add it to map
			result = evaluateExpression(parsedString);
			varMap[var] = result;
		}
		else {
            //cout << "not an assignment\n";

			//evaluate the parsedString;
			result = evaluateExpression(parsedString);
			cout << result << "\n";
		}
		getline(cin, input);
	}
	return 0;
}
