/*
implementing floyd's cycle find algorithm to detect if a linked list has cycle 
*/


/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    }
*/


bool has_cycle(Node* head) {
	if(head == NULL) {
		return 0;
	}
	Node* fast = head;
	Node* slow = head;
	while(fast != NULL && fast->next != NULL) { 
		slow = slow->next;
		fast = fast->next->next;
		if(fast == slow) {
			return 1;
		}
	}
	return 0;
}



//part2, I used unordered_map, but does not pass the test case
#include <unordered_map>
unordered_map<Node,bool> myMap;
bool has_cycle(Node* head) {
    if(head == NULL) {
        return false;
    }
    while(head->next != NULL) {
        myMap.emplace(head, true);
        Node* temp = head->next;
        if(myMap.find(temp) != myMap.end()) {
            return true;
        }
        head = temp;
    }
    return false;
}
bool 