#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int data;
	int left;
	int right;
};

vector<Node*> arr;

void preOrder(Node* root) {
	cout << root->data << " ";
	if(root->left != -1) {
		cout << arr[root->left]->data << " ";
	}
	if(root->right != -1) {
		cout << arr[root->right]->data << " ";
	}
}

void inOrder(Node* root) {
	if(root->left != -1) {
		cout << arr[root->left]->data << " ";
	}
	cout << root->data << " ";
	if(root->right != -1) {
		cout << arr[root->right]->data << " ";
	}
}

void postOrder(Node* root) {
	if(root->left != -1) {
		cout << arr[root->left]->data << " ";
	}
	if(root->right != -1) {
		cout << arr[root->right]->data << " ";
	}
	cout << root->data << " ";
}

int main() {
	int N;
	cin >> N;
	//Node* arr[N];

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
