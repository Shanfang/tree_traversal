#include <iostream>
#include <stack>
#include <queue>
#include <string>
//here are the algorithm for converting infix form to postfix

While (we have not reached the end of Q)
        If (an operand is found)
           Add it to P
        End-If
        If (a left parenthesis is found) 
           Push it onto the stack
        End-If
        If (a right parenthesis is found) 
           While (the stack is not empty AND the top item is
                  not a left parenthesis)
              Pop the stack and add the popped value to P
           End-While
           Pop the left parenthesis from the stack and discard it 
        End-If
        If (an operator is found)
           If (the stack is empty or if the top element is a left
               parenthesis)
              Push the operator onto the stack
           Else  
              While (the stack is not empty AND the top of the stack 
                     is not a left parenthesis AND precedence of the                  
                     operator <= precedence of the top of the stack)
                 Pop the stack and add the top value to P
              End-While
              Push the latest operator onto the stack     
           End-If  
        End-If
     End-While
     While (the stack is not empty)
        Pop the stack and add the popped value to P
     End-While

	 
	 //here are some java code for checking precedence and divide by 0
	  public static boolean hasPrecedence(char op1, char op2)
    {
        if (op2 == '(' || op2 == ')')
            return false;
        if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
            return false;
        else
            return true;
    }
 
    // A utility method to apply an operator 'op' on operands 'a' 
    // and 'b'. Return the result.
    public static int applyOp(char op, int b, int a)
    {
        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
                throw new
                UnsupportedOperationException("Cannot divide by zero");
            return a / b;
        }
        return 0;
    }    
	

	
	
	//the c++ code for getting precedence
#include <iostream>
#include<stack>
#include<vector>
#include<cmath>
#include <string.h>
using namespace std;
 
int getPrecedence(char c)
{
	if(c=='+'||c=='-')
	{
		return 1;
	}
	else if(c=='*' || c=='/')
	{
		return 2;
	}
	else if(c=='^')
	{
		return 3;
	}
 
	return -1;
}	