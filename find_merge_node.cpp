/* a smart way to find the merge node of two linked lists
	the two lists are guaranteed to merge
*/
struct Node {
	int data;
	Node* next;
}

int findMergeNode(Node* headA, Node* headB) {
	Node* currA = headA;
	Node* currB = headB;
	while(currA != currB) {
		if(currA->next == NULL) {
			currA = headB;
		}
		else {
			currA = currA->next;
		}
		if(currB->next == NULL){
			currB = headA;
		}
		else{
			currB = currB->next;
		}
	}
	return currA->data;
}