#include <cmath>
#include <cstdio>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int N;
    string line;
    stack<int> myStack;
    vector<int> myVector;
    
    cin >> N;
    int type;
    int element;
    int max = 0;
    for (int i  = 0; i < N; i++) {
        cin >> type;
        if(type == 1) {
            cin>> element;
            if(myStack.empty()) {
                myStack.push(element);               
            }
            else {
                myStack.push(std::max(element, myStack.top()));
            }
        }
        else if(type == 2) {
            myStack.pop();
        }
 
        //search the vector to find the maximum value
        else {
            cout  << myStack.top() << "\n";
        }
    }
    return 0;
}