//from hackerrank
https://www.hackerrank.com/challenges/delete-duplicate-value-nodes-from-a-sorted-linked-list
/*
  Remove all duplicate elements from a sorted linked list
  Node is defined as 
  struct Node
  {
     int data;
     struct Node *next;
  }
*/
Node* RemoveDuplicates(Node *head)
{
    
   //for empty list
    if(head == NULL) {
        return head;
    } 
    
    //non-empty list
    Node* pre = head;
    Node* temp;
    while(pre->next != NULL) {
        temp = pre->next;
        while(temp->data == pre->data && temp->next != NULL) {
            temp = temp->next;
        }
		if(temp->data == pre->data) {
			pre->
		}
        pre->next = temp;
        pre = temp;
    }
   return head; 
}
