#include <iostream>

using namespace std;

int DesiredNumber = 0;

struct tree {
	int key;
	int number; 
	tree* left;
	tree* right;
};

tree* root = nullptr;
tree* result = nullptr;

tree* FindElementByNumber(tree* Base) {
	if (Base == nullptr) {
		return nullptr;
	}

	if (Base->number == DesiredNumber) {
		return Base;
	}

	if (Base->right != nullptr && DesiredNumber <= Base->right->number) {
		return FindElementByNumber(Base->right);
	}
	else if (Base->left != nullptr) {
		return FindElementByNumber(Base->left);
	}

	return nullptr;
}

tree* FindElementLessNumber(int K) {
	DesiredNumber = root->number - K;
	tree* root2 = FindElementByNumber(root);
	return root2;
}

tree* createNode(int key) {
	tree* newNode = new tree;
	newNode->key = key;
	newNode->number = 1;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

tree* insertNode(tree* root, int key) {
	if (root == nullptr) {
		return createNode(key);
	}

	if (key < root->key) {
		root->left = insertNode(root->left, key);
		root->number++;
	}
	else if (key > root->key) {
		root->right = insertNode(root->right, key);
		root->number++;
	}

	return root;
}

int main()
{
	root = insertNode(root, 10);
	insertNode(root, 5);
	insertNode(root, 15);
	insertNode(root, 3);
	insertNode(root, 7);
	insertNode(root, 12);
	insertNode(root, 18);

	result = FindElementLessNumber(4);
	cout << result->key << endl;
	cout << result->number;
	return 0;
}
