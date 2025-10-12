#include <iostream>
#include <vector>
using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
public:
    // Check if node is a leaf
    bool isLeaf(Node* root) {
        return !root->left && !root->right;
    }
    
    // Add left boundary (excluding leaf nodes)
    void addLeftBoundary(Node* root, vector<int>& result) {
        Node* curr = root->left;
        while (curr) {
            if (!isLeaf(curr)) {
                result.push_back(curr->data);
            }
            // Move to left if exists, otherwise right
            if (curr->left) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
    }
    
    // Add all leaf nodes (left to right)
    void addLeaves(Node* root, vector<int>& result) {
        if (isLeaf(root)) {
            result.push_back(root->data);
            return;
        }
        if (root->left) addLeaves(root->left, result);
        if (root->right) addLeaves(root->right, result);
    }
    
    // Add right boundary (excluding leaf nodes) in reverse
    void addRightBoundary(Node* root, vector<int>& result) {
        Node* curr = root->right;
        vector<int> temp;
        
        while (curr) {
            if (!isLeaf(curr)) {
                temp.push_back(curr->data);
            }
            // Move to right if exists, otherwise left
            if (curr->right) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        
        // Add in reverse order (bottom to top)
        for (int i = temp.size() - 1; i >= 0; i--) {
            result.push_back(temp[i]);
        }
    }
    
    // Main function for boundary traversal
    vector<int> boundaryTraversal(Node* root) {
        vector<int> result;
        
        if (!root) return result;
        
        // Add root if it's not a leaf
        if (!isLeaf(root)) {
            result.push_back(root->data);
        }
        
        // Add left boundary
        addLeftBoundary(root, result);
        
        // Add all leaf nodes
        addLeaves(root, result);
        
        // Add right boundary
        addRightBoundary(root, result);
        
        return result;
    }
};

// Utility function to print the result
void printResult(vector<int>& result) {
    cout << "Boundary Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    /* Example Tree:
            20
           /  \
          8    22
         / \    \
        4  12   25
          /  \
         10  14
    */
    
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);
    root->right->right = new Node(25);
    
    Solution sol;
    vector<int> result = sol.boundaryTraversal(root);
    printResult(result);
    // Output: 20 8 4 10 14 25 22
    
    cout << "\nExample 2:\n";
    /* Example Tree 2:
            1
           / \
          2   3
         / \
        4   5
    */
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->left->right = new Node(5);
    
    vector<int> result2 = sol.boundaryTraversal(root2);
    printResult(result2);
    // Output: 1 2 4 5 3
    
    return 0;
}

/* 
EXPLANATION:

For the tree:
        20
       /  \
      8    22
     / \    \
    4  12   25
      /  \
     10  14

Boundary Traversal Steps:
1. Root: 20
2. Left Boundary (top to bottom, no leaves): 8
3. Leaf Nodes (left to right): 4, 10, 14, 25
4. Right Boundary (bottom to top, no leaves): 22

Result: 20 8 4 10 14 25 22

TIME COMPLEXITY: O(N) - visit each node once
SPACE COMPLEXITY: O(H) - recursion stack for height H
*/