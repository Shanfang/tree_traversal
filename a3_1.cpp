#include<iostream>
#include<vector>

using namespace std;

struct Node {
    int data;
	int left;
	int right;
};
vector<Node*> arr1;

void preOrder(Node* root) {
	cout << root->data << " ";
	if(root->left != -1) {
		preOrder(arr1[root->left]);
	}
	if(root->right != -1) {
		preOrder(arr1[root->right]);
	}
}

void inOrder(Node* root) {
    if(root->left != -1) {
		inOrder(arr1[root->left]);
	}
	cout << root->data << " ";
	if(root->right != -1) {
		inOrder(arr1[root->right]);
	}
}

void postOrder(Node* root) {
	if(root->left != -1) {
		postOrder(arr1[root->left]);
	}
	if(root->right != -1) {
		postOrder(arr1[root->right]);
	}
	cout << root->data << " ";
}

int main() {

	//preorder/inorder/postorder traversal
	int N;
	cin >> N;
	for(int i = 0; i < N; i++) {
        Node* node = new Node();
		cin >> node->data >> node->left >> node->right;
        arr1.push_back(node);
	}

	Node* root1  = arr1[0];
	preOrder(root1);
	cout << "\n";
	inOrder(root1);
	cout << "\n";
	postOrder(root1);
	cout << "\n";
	return 0;
}
