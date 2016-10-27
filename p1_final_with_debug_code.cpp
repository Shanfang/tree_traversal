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

/*parsing string with multiple delimiters
for each character, check if it is operator(call respective function)/number(int&dot)/variable(all characters && not reserved word let && not constants)

*/
/*error handling
1) divide by 0, when poping a /, check if the second operand is 0
2) while parsing the string, if it is a variable, check map to see if it is defined
*/

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
                cout << "Pushing element " << temp << " into vector\n";
			}
            //tokeVector.push_back(temp);
			tokeVector.push_back(line.substr(pos, 1));
		}
		prev = pos + 1;
	}
	//tokeVector.push_back(line.substr(prev));
	if (prev < line.length()) {
        temp = line.substr(prev, string::npos);
        string::iterator endPos = remove(temp.begin(), temp.end(), ' ');
        temp.erase(endPos, temp.end());
		tokeVector.push_back(temp);
	}
}


    cout << "string has been parsed successfully\n";
    for(vector<string>::iterator it = tokeVector.begin(); it != tokeVector.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";

cout << "number of the parsed string is " << tokeVector.size() << endl;
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
    //else (op == "(") {
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
    cout << "In infixToPostfix function\n";
    /*for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        cout << *it << " " << "\n";
    }
    cout <<  "\n";*/
	//push the tokens onto operatorStack and operandQueue accordingly
	//for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {

	for(size_t i = 0; i < tokens.size(); ++i) {
    cout << "The value is " << tokens[i] << endl;
		if(isOperand(tokens[i])) {
			operandQueue.push(tokens[i]);
			//cout << "pushing operand " <<*it << " onto queue\n";
            //cout << "Is the operand queue empty? " << operandQueue.empty() << "\n";
		}
		else if(tokens[i] == "(") {
			operatorStack.push(tokens[i]);
			cout << "Pushing operator " <<tokens[i] << " onto stack\n";
		}
		else if(tokens[i] == ")") {
			while(!operatorStack.empty() && operatorStack.top()!= "(") {
				operandQueue.push(operatorStack.top());
                cout << "Poping operator " << operatorStack.top() << " from stack to queue\n";
				operatorStack.pop();
			}

			//pop left parenthese off stack and discard it
			cout << "Poping " << operatorStack.top() << " off operatorStack\n";
			operatorStack.pop();
		}
		//else if(isOperator(*it)) {
		else {
			if(operatorStack.empty() || operatorStack.top() == "(") {
			//if(operatorStack.empty() || operatorStack.top() == "(" || isFunction(*it)) {
				operatorStack.push(tokens[i]);
			//cout << "pushing operator " <<*it << " onto stack\n";
			}
			else {
				while(!operatorStack.empty() && operatorStack.top() != "(" && precedence(tokens[i]) <= precedence(operatorStack.top())) {
						operandQueue.push(operatorStack.top());
                        //cout << "Pushing operators " << operatorStack.top() << " from stack to queue\n";
						operatorStack.pop();
				}
                operatorStack.push(tokens[i]);
                //cout << "Pushing operator " << *it << " onto stack\n";
			}
		}
	}

	//cout << "Poping elements from stack to queue\n";
	//pop the operatorStack and add them to the end of operandQueue until the stack is empty
    cout << "Is the operator stack empty now? " << operatorStack.empty() << "\n";
	while(!operatorStack.empty()) {
		cout << "Poping " << operatorStack.top() << " from stack to queue\n";
		operandQueue.push(operatorStack.top());
		operatorStack.pop();
	}
    //cout << "The operator stack is empty now!\n";
	//cout << "Is the operand queue empty? " << operandQueue.empty() << "\n";
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
	//any other operators?????
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
    //cout << "In evaluateExpression function\n";
	queue<string> postFixQ;
	stack<double> stack;

	postFixQ = infixToPostfix(expression);
	//cout << "After calling infixToPostfix function, is the queue empty? " << postFixQ.empty() << "\n";


	//using a stack to evaluate the input queue, convert operands from queue to double
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
			//cout << "The function " << token << " only takes one operand " << op1 << "\n";
			result = calcFunct(op1, token);
			//cout << "The function evaluates to " << result << "\n";
			stack.push(result);
		}

		//if the token is a regular operator, pop two operands form stack and do calculation
		else {
			op2 = stack.top();
			//cout << "operand op2 is " << op2 << "\n";
			stack.pop();
			op1 = stack.top();
			//cout << "operand op1 is " << op1 << "\n";
			stack.pop();
			if(token == "/" && op2 == 0) {
            //if(op2 == 0) {
                expResult = "Division";
                cout << "Oops, bad division\n";
                return expResult;
            }
                result = calcResult(op1, op2, token);
                cout << "In evaluateExpression function, the result is " << result << "\n";
                stack.push(result);
			}
		}
        //stringstream(stack.top()) >> expResult;
        stringstream ss;
        ss << stack.top();

        cout << "Top of the result stack is " << stack.top() << endl;
        //expResult = to_string(stack.top());
        return ss.str();
	}



int main() {
	vector<string> parsedString;
	string input;
    string output;
    string var;
    bool assignment = false;

    varMap.emplace("Pi","3.14169");
    varMap.emplace("e", "2.718");
	getline(cin, input);


    //if the input is empty, discard it and request new input
    while(input.empty()) {
        cin.clear();
        cin.ignore(256 ,'\n');
        getline(cin, input);
    }

    /*parsedString = parseString(input);
    cout << "string has been parsed successfully\n";
    for(vector<string>::iterator it = parsedString.begin(); it != parsedString.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";*/

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

        //get the variable name
        int varStart = 4;

        //varEnd is the position one past the last char of var
        int varEnd = input.find_first_of(' ', varStart);
        var = input.substr(varStart, varEnd - varStart );
        input = input.substr(varEnd + 2, input.length()-varEnd - 2);
    }

	//accept input as long as it is not "quit"
	while(input != "quit") {

        //if it is an assignment
		parsedString = parseString(input);

		/*cout << "string has been parsed successfully\n";
		for(vector<string>::iterator it = parsedString.begin(); it != parsedString.end(); it++) {
            cout << *it << " ";
		}
		cout << "\n";*/

        //evaluate the expression after checking potential errors
        output = evaluateExpression(parsedString);
        if(assignment && output != "Division" && output != "Undeclared") {
            //varMap[var] = atof(output.c_str());
            //update value of a certain key , or put a new pair into map
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
    //discard any whitespace before the first valid character
        input = input.substr(num, input.size() - num);
        if (input.substr(0, 4) == "quit") {
            input = "quit";
        }
        else if(input.substr(0, 3) == "let" && input.at(3) == ' ') {
            assignment =  true;

            //get the variable name
            int varStart = 4;

            //varEnd is the position one past the last char of var
            int varEnd = input.find_first_of(' ', varStart);
            var = input.substr(varStart, varEnd - varStart );
            input = input.substr(varEnd + 2, input.length()-varEnd - 2);
        }
	}
	return 0;
}
