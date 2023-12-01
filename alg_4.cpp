#include <algorithm>
#include <random>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int value;
    int data;
    Node* left;
    Node* right;
};

Node* CreateNode(Node* node, const int& value) {
    node = new Node;
    node->value = value;
    node->data = 0;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void InsertNode(Node* node, const int& key) {
    if (key < node->value) {
        if (node->left == nullptr) node->left = CreateNode(node->left, key);
        else InsertNode(node->left, key);
    }
    else {
        if (node->right == nullptr) node->right = CreateNode(node->right, key);
        else InsertNode(node->right, key);
    }
}

int GetTreeDepth(Node* root, int depth = 0) {
    if (!root) return depth;

    int left_depth = GetTreeDepth(root->left, depth + 1);
    int right_depth = GetTreeDepth(root->right, depth + 1);

    return max(left_depth, right_depth);
}

int CountLeafNodes(Node* root) {
    if (!root) return 0;

    if (!root->left && !root->right) return 1;

    int left_count = CountLeafNodes(root->left);
    int right_count = CountLeafNodes(root->right);

    root->data = left_count + right_count;

    return root->data;
}

void InitializeLeafCounts(Node* root) {
    if (!root) return;

    CountLeafNodes(root);
    InitializeLeafCounts(root->left);
    InitializeLeafCounts(root->right);
}

void InitializeMatrix(Node* root, vector<vector<string>>& matrix, int current_coords, int level = 0) {
    if (!root) return;

    matrix[level][current_coords].replace(0, 1, to_string(root->data));
    int level_gap = pow(2, GetTreeDepth(root) - level) / 2;

    InitializeMatrix(root->left, matrix, current_coords - level_gap, level + 1);
    InitializeMatrix(root->right, matrix, current_coords + level_gap, level + 1);
}

void InitializeTree(Node*& root, const int& n) {
    random_device rd;
    mt19937 gen(rd());

    vector<int> values(n);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end(), gen);

    for (const int& i : values)
        if (root == nullptr) root = CreateNode(root, i);
        else InsertNode(root, i);

    InitializeLeafCounts(root);
}

void DisplayTree(Node* root) {
    int depth = GetTreeDepth(root);
    vector<vector<string>> matrix(depth + 1, vector<string>(2 * pow(2, depth) - 1, " "));

    InitializeMatrix(root, matrix, matrix[0].size() / 2);

    for (const auto& line : matrix) {
        for (const auto& elem : line) cout << elem;
        cout << endl;
    }
}

int main() {
    Node* root = nullptr;
    InitializeTree(root, 8);
    DisplayTree(root);

    return 0;
}


