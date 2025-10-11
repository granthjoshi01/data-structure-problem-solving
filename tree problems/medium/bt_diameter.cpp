/**
 * Diameter of Binary Tree
 * 
 * Problem: The diameter of a binary tree is the length of the longest path between
 * any two nodes in a tree. This path may or may not pass through the root.
 * The length of a path is the number of edges between nodes.
 * 
 * Approach: Post-order DFS traversal
 * - For each node, calculate the height of left and right subtrees
 * - The diameter at any node = left height + right height (edges through that node)
 * - Track the maximum diameter found across all nodes
 * - Return the height for parent node calculations
 * 
 * Time Complexity: O(N) where N is the number of nodes
 * Space Complexity: O(H) where H is the height of the tree (recursion stack)
 * 
 * Author: [Your Name]
 * Date: October 11, 2025
 */

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    
    // Constructors
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /**
     * Calculates the diameter of a binary tree
     * @param root: Root node of the binary tree
     * @return: Length of the longest path between any two nodes (number of edges)
     */
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;  // Track maximum diameter found
        depth(root, diameter);
        return diameter;
    }
    
private:
    /**
     * Helper function to calculate depth and update diameter using post-order traversal
     * @param root: Current node being processed
     * @param diameter: Reference to the maximum diameter found so far
     * @return: Depth (height) of the current subtree
     */
    int depth(TreeNode* root, int& diameter) {
        // Base case: null node has depth 0
        if (root == NULL) 
            return 0;
        
        // Recursively calculate depth of left and right subtrees
        int lh = depth(root->left, diameter);
        int rh = depth(root->right, diameter);
        
        // Update diameter: longest path through current node
        // is the sum of left height + right height (number of edges)
        diameter = std::max(diameter, lh + rh);
        
        // Return height of current subtree (max of left/right + 1 for current node)
        return 1 + max(lh, rh);
    }
};

// Utility function to create a new tree node
TreeNode* newNode(int val) {
    return new TreeNode(val);
}

// Utility function to print tree in level-order (for verification)
void printTree(TreeNode* root) {
    if (!root) {
        cout << "Empty tree" << endl;
        return;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    
    cout << "Tree (level-order): ";
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (node) {
            cout << node->val << " ";
            q.push(node->left);
            q.push(node->right);
        } else {
            cout << "null ";
        }
    }
    cout << endl;
}

// Utility function to delete tree and free memory
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Solution solution;
    
    // Test Case 1: root = [1,2,3,4,5]
    // Tree:       1
    //            / \
    //           2   3
    //          / \
    //         4   5
    // Expected output: 3 (path: 4->2->1->3 or 5->2->1->3, length = 3 edges)
    cout << "Test Case 1:" << endl;
    TreeNode* root1 = newNode(1);
    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left = newNode(4);
    root1->left->right = newNode(5);
    printTree(root1);
    cout << "Diameter: " << solution.diameterOfBinaryTree(root1) << endl;
    cout << "Expected: 3" << endl << endl;
    deleteTree(root1);
    
    // Test Case 2: root = [1,2]
    // Tree:   1
    //        /
    //       2
    // Expected output: 1 (path: 2->1, length = 1 edge)
    cout << "Test Case 2:" << endl;
    TreeNode* root2 = newNode(1);
    root2->left = newNode(2);
    printTree(root2);
    cout << "Diameter: " << solution.diameterOfBinaryTree(root2) << endl;
    cout << "Expected: 1" << endl << endl;
    deleteTree(root2);
    
    // Test Case 3: Single node
    // Tree: 1
    // Expected output: 0 (no edges)
    cout << "Test Case 3:" << endl;
    TreeNode* root3 = newNode(1);
    printTree(root3);
    cout << "Diameter: " << solution.diameterOfBinaryTree(root3) << endl;
    cout << "Expected: 0" << endl << endl;
    deleteTree(root3);
    
    // Test Case 4: Skewed tree (left)
    // Tree:     1
    //          /
    //         2
    //        /
    //       3
    //      /
    //     4
    // Expected output: 3 (path: 4->3->2->1, length = 3 edges)
    cout << "Test Case 4:" << endl;
    TreeNode* root4 = newNode(1);
    root4->left = newNode(2);
    root4->left->left = newNode(3);
    root4->left->left->left = newNode(4);
    printTree(root4);
    cout << "Diameter: " << solution.diameterOfBinaryTree(root4) << endl;
    cout << "Expected: 3" << endl << endl;
    deleteTree(root4);
    
    // Test Case 5: Diameter doesn't pass through root
    // Tree:         1
    //              /
    //             2
    //            / \
    //           3   4
    //          / \
    //         5   6
    // Expected output: 4 (path: 5->3->2->4 or 6->3->2->4, length = 4 edges)
    cout << "Test Case 5:" << endl;
    TreeNode* root5 = newNode(1);
    root5->left = newNode(2);
    root5->left->left = newNode(3);
    root5->left->right = newNode(4);
    root5->left->left->left = newNode(5);
    root5->left->left->right = newNode(6);
    printTree(root5);
    cout << "Diameter: " << solution.diameterOfBinaryTree(root5) << endl;
    cout << "Expected: 4" << endl << endl;
    deleteTree(root5);
    
    // Test Case 6: Balanced tree
    // Tree:         1
    //              / \
    //             2   3
    //            / \
    //           4   5
    //          /
    //         6
    // Expected output: 4 (path: 6->4->2->5 or 6->4->2->1->3, length = 4 edges)
    cout << "Test Case 6:" << endl;
    TreeNode* root6 = newNode(1);
    root6->left = newNode(2);
    root6->right = newNode(3);
    root6->left->left = newNode(4);
    root6->left->right = newNode(5);
    root6->left->left->left = newNode(6);
    printTree(root6);
    cout << "Diameter: " << solution.diameterOfBinaryTree(root6) << endl;
    cout << "Expected: 4" << endl << endl;
    deleteTree(root6);
    
    return 0;
}