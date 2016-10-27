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
unordered_map<string, string> varMap;

vector<string> parseString(string input) {
vector<string> tokeVector;
stringstream stringStream(input);
string line;
string temp;

while (getline(stringStream, line)) {
	size_t prev = 0, pos;
	while ((pos = line.find_first_of("+-*/^()=", prev)) != string::npos) {
		if (pos >= prev) {
			temp = line.substr(prev, pos - prev);

			//remove space in and after the substring
			string::iterator endPos = remove(temp.begin(), temp.end(), ' ');

            //erase characters in the range[endPos, temp.end())
			temp.erase(endPos, temp.end());

			if(!temp.empty()) {
                tokeVector.push_back(temp);
			}
			tokeVector.push_back(line.substr(pos, 1));
		}
		prev = pos + 1;
	}

	//handle the last substring
	if (prev < line.length()) {
        temp = line.substr(prev, string::npos);
        string::iterator endPos = remove(temp.begin(), temp.end(), ' ');
        temp.erase(endPos, temp.end());
		tokeVector.push_back(temp);
	}
}
	return tokeVector;
}


int precedence(string op) {
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
	else if(op == "sin" || op == "cos" || op == "log") {
        return 5;
	}
    else {
		return 6;
	}
}

//check if a token is a function
bool isFunction(string token) {
	return (token == "sin" || token == "cos" || token == "log");
}

//check if a token is an operator
bool isOperator(string token) {
 return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

//check if a token is an operand
bool isOperand(string token) {
    if(isdigit(token.at(0))) {
      return true;
    }
    else if(isalpha(token.at(0)) && !(isFunction(token))) {
       return true;
    }
	return false;
}

//implementing shunting yard algorithm to transform infix to postfix
queue<string> infixToPostfix(vector<string> tokens) {
	stack<string> operatorStack;
	queue<string> operandQueue;

	//push the tokens onto operatorStack and operandQueue accordingly
	for(size_t i = 0; i < tokens.size(); ++i) {
		if(isOperand(tokens[i])) {
			operandQueue.push(tokens[i]);
		}
		else if(tokens[i] == "(") {
			operatorStack.push(tokens[i]);
		}
		else if(tokens[i] == ")") {
			while(!operatorStack.empty() && operatorStack.top()!= "(") {
				operandQueue.push(operatorStack.top());
				operatorStack.pop();
			}

			//pop left parenthesis off stack and discard it
			operatorStack.pop();
		}
		else {
			if(operatorStack.empty() || operatorStack.top() == "(") {
				operatorStack.push(tokens[i]);
			}
			else {
				while(!operatorStack.empty() && operatorStack.top() != "(" && precedence(tokens[i]) <= precedence(operatorStack.top())) {
						operandQueue.push(operatorStack.top());
						operatorStack.pop();
				}
                operatorStack.push(tokens[i]);
			}
		}
	}

	//pop the operatorStack and add them to the end of operandQueue until the stack is empty
	while(!operatorStack.empty()) {
		operandQueue.push(operatorStack.top());
		operatorStack.pop();
	}
	return operandQueue;
}

//calculate one step of calculation
double calcResult(double& op1, double& op2, string& opt) {
	double result;
	if(opt == "+") {
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
	return result;
}

//calculate the function
double calcFunct(double op1, string& opt) {
    double result;
    if(opt == "sin") {
        result = sin(op1);
    }
    else if(opt == "cos") {
        result = cos(op1);
    }
    else {
        result = log(op1);
    }
    return result;
}

/*take a vector of string as input, call infixToPostfix function to get a queue of tokens
  then push the returned queue to a stack and use the stack to evaluate the expression
*/
string evaluateExpression(vector<string> expression) {
	queue<string> postFixQ;
	stack<double> stack;
	postFixQ = infixToPostfix(expression);

    string expResult;
    double result;
    double op1;
    double op2;
    string token;
	while(!postFixQ.empty()) {
		token = postFixQ.front();
        postFixQ.pop();

		//if the front of queue is an operand, push it onto stack
		if(isOperand(token)) {

           //check if the operand is a variable and if it is declared
           if(isdigit(token.at(0))) {
                stack.push(atof(token.c_str()));
           }
            else if(varMap.find(token) != varMap.end()) {
                stack.push(atof((varMap.find(token)->second).c_str()));
            }
            else {
                expResult = "Undeclared";
                return expResult;
            }
		}

		//if the operator is a function, pop one operand from the stack
		else if(isFunction(token)) {
			op1 = stack.top();
			result = calcFunct(op1, token);
			stack.push(result);
		}

		//if the token is a regular operator, pop two operands form stack and do calculation
		else {
			op2 = stack.top();
			stack.pop();
			op1 = stack.top();
			stack.pop();
			if(token == "/" && op2 == 0) {
                expResult = "Division";
                return expResult;
            }
                result = calcResult(op1, op2, token);
                stack.push(result);
			}
		}

		//use stringstream to convert double type into basic string
        stringstream ss;
        ss << stack.top();
        return ss.str();
	}

int main() {
	vector<string> parsedString;
	string input;
    string output;
    string var;
    bool assignment = false;

    //store constants into variable map
    varMap.emplace("Pi","3.14169");
    varMap.emplace("e", "2.718");
	getline(cin, input);

    //if the input is empty, discard it and request new input
    while(input.empty()) {
        cin.clear();
        cin.ignore(256 ,'\n');
        getline(cin, input);
    }

    //iterate the input to find the first character that is not a whitespace, and count the number of space encountered
    int num = 0;
    string::iterator it = input.begin();
    while(*it ==' ' && it != input.end()) {
       it++;
       num++;
    }

    //discard any whitespace before the first valid character
    input = input.substr(num, input.size() - num);
    if (input.substr(0, 4) == "quit") {
        input = "quit";
    }
    else if(input.substr(0, 3) == "let" && input.at(3) == ' ') {
        assignment =  true;

        //get the variable name, varEnd is the position one past the last char of var
        int varStart = 4;
        int varEnd = input.find_first_of(' ', varStart);
        var = input.substr(varStart, varEnd - varStart );
        input = input.substr(varEnd + 2, input.length()-varEnd - 2);
    }

	//accept input as long as it is not "quit"
	while(input != "quit") {
		parsedString = parseString(input);
        output = evaluateExpression(parsedString);

        //update value of an existing key , or put a new pair into map
        if(assignment && output != "Division" && output != "Undeclared") {
            if(varMap.find(var) != varMap.end()) {
                varMap[var] = output;
            }
            else {
            varMap.emplace(var, output);
            }
        assignment = false;
        }
        else if(output == "Division") {
            cout << "Division-By-Zero\n";
        }
        else if(output == "Undeclared") {
            cout << "Undeclared-Variable\n";
        }
        else {
            cout << output << "\n";
        }

        //continue getting input and pre-parse it
        getline(cin, input);
        while(input.empty()) {
            cin.clear();
            cin.ignore(256 ,'\n');
            getline(cin, input);
        }
        int num = 0;
        string::iterator it = input.begin();
        while(*it == ' ' && it != input.end()) {
           it++;
           num++;
        }
        input = input.substr(num, input.size() - num);
        if (input.substr(0, 4) == "quit") {
            input = "quit";
        }
        else if(input.substr(0, 3) == "let" && input.at(3) == ' ') {
            assignment =  true;
            int varStart = 4;
            int varEnd = input.find_first_of(' ', varStart);
            var = input.substr(varStart, varEnd - varStart );
            input = input.substr(varEnd + 2, input.length()-varEnd - 2);
        }
	}
	return 0;
}
