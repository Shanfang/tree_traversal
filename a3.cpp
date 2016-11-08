#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
	int left;
	int right;
	//Node(int d = -1, int l = -1, int r = -1):data(d), left(l), right(r) {}
};
vector<Node> arr;


void preOrder(Node root) {
	cout << root.data << " ";
	if(root.left != -1) {
		preOrder(arr[root.left]);
	}
	if(root.right != -1) {
		preOrder(arr[root.right]);
	}
}

void inOrder(Node root) {
	if(root.left != -1) {
		inOrder(arr[root.left]);
	}
	cout << root.data << " ";
	if(root.right != -1) {
		inOrder(arr[root.right]);
	}
}

void postOrder(Node root) {
	if(root.left != -1) {
		postOrder(arr[root.left]);
	}
	if(root.right != -1) {
		postOrder(arr[root.right]);
	}
	cout << root.data << " ";
}

int main() {
	int N;
	cin >> N;

	//get input
	for(int i = 0; i < N; i++) {
        Node node;
		cin >> node.data >> node.left >> node.right;
        arr.push_back(node);
	}

	Node root  = arr[0];
	preOrder(root);
	cout << "\n";
	inOrder(root);
	cout << "\n";
	postOrder(root);
	cout << "\n";
	return 0;
}