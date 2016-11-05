#include <iostream>


using namespace std;
struct Node {
	int data;
	Node* left;
	Node* right;
};

void preOrder(Node* root) {
	cout << root->data << " ";
	if(root->left->data != -1) {
		cout << root->left->data << " ";
	}
	if(root->right->data != -1) {
		cout << root->right->data << " ";
	}
}

void inOrder(Node* root) {
	if(root->left->data != -1) {
		cout << root->left->data << " ";
	}
	cout << root->data << " ";
	if(root->right->data != -1) {
		cout << root->right->data << " ";
	}
}

void postOrder(Node* root) {
	if(root->left->data != -1) {
		cout << root->left->data << " ";
	}
	if(root->right->data != -1) {
		cout << root->right->data << " ";
	}
	cout << root->data << " ";
}

int main() {
	int N;
	cin >> N;
	Node* arr[N];
	
	//get input
	for(int i = 0; i < N; i++) {
		//Node* node;
		cin >> arr[i]->data >> arr[i]->left >> arr[i]->right;	
	}
	
	Node* root  = arr[0];
	
	//preorder traversal
	preOrder(root);
	cout << "\n";
	inOrder(root);
	cout << "\n";
	postOrder(root);
	cout << "\n";	
	return 0;
}