#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Node {
    int data;
	int left;
	int right;
	//Node(int d = -1, int l = -1, int r = -1):data(d), left(l), right(r) {}
};
vector<Node*> arr1;
vector<Node*> arr2;

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

void levelOrder(Node* root) {
	queue<Node*> myQueue;
	if(root->data != -1) {
		myQueue.push(root);
	}
	while(!myQueue.empty()) {
		Node* newNode = myQueue.front();
		myQueue.pop();
		cout << newNode->data << " ";
		if(newNode->left != -1) {
			myQueue.push(arr2[newNode->left]);
		}
		if(newNode->right != -1) {
			myQueue.push(arr2[newNode->right]);
		}
	}
}

struct node {
    int data;
	node* left;
	node* right;
	//Node(int d = data, node* l = NULL, node* r = NULL):data(d), left(l), right(r) {}
};

int search(int arr[], int start, int end, int num) {
    for(int i = start; i < end; i++) {
        if(arr[i] == num) {
            return i;
        }
    }
}

node* BuildTree(int postorder[], int inorder[], int start, int end) {
    static int postindex = end-1;
	//If start>end return NULL;
	node* newNode;
	newNode->data = postorder[postindex];
	postindex--;
	if(start==end) {
        cout << "This is in building tree " << newNode->data << endl;
        return newNode;
	}
	int searchindex = search(inorder,start,end, newNode->data);
	newNode->right = BuildTree(postorder, inorder, searchindex+1,end);
	newNode->left = BuildTree(postorder,inorder,start,searchindex-1);
	return newNode;
}

void pLevelOrder(node* root) {
	queue<node*> myQueue;
	if(root != NULL) {
		myQueue.push(root);
	}
	while(!myQueue.empty()) {
		node* node = myQueue.front();
		myQueue.pop();
		cout << node->data << " ";
		if(node->left != NULL) {
			myQueue.push(node->left);
		}
		if(node->right != NULL) {
			myQueue.push(node->right);
		}
	}
}

int main() {
	/*int N;
	cin >> N;

	//get input
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
	cout << "\n";*/

	//for question 2
	int M;
	cin >> M;
	for(int i = 0; i < M; i++) {
        Node* node = new Node();
		cin >> node->data >> node->left >> node->right;
        arr2.push_back(node);
	}

	Node* root2  = arr2[0];
	levelOrder(root2);
    cout << "\n";
    /*int X;
    cin >> X;
    int postOrder[X], inOrder[X];
    int value;
    for(int i = 0; i < X; i++) {
        cin >> value;
        postOrder[i] = value;
    }
    for(int i = 0; i < X; i++) {
        cin >> value;
        inOrder[i] = value;
    }
    node* n = BuildTree(postOrder, inOrder, 0, X-1);
    cout << "Tree has been built\n";
    pLevelOrder(n);*/

	return 0;
}
