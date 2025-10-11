/**
 * Binary Tree Maximum Path Sum
 * 
 * Problem: Find the maximum path sum in a binary tree where a path is defined as
 * any sequence of nodes from some starting node to any node in the tree along 
 * the parent-child connections. The path must contain at least one node and does
 * not need to go through the root.
 * 
 * Approach: Post-order DFS traversal
 * - For each node, calculate the maximum path sum that can be extended upward
 * - Track the global maximum path sum that may include paths turning at any node
 * - Ignore negative contributions from subtrees using max(0, subtree_sum)
 * 
 * Time Complexity: O(N) where N is the number of nodes
 * Space Complexity: O(H) where H is the height of the tree (recursion stack)
 * 
 */

#include <iostream>
#include <climits>
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
     * Finds the maximum path sum in a binary tree
     * @param root: Root node of the binary tree
     * @return: Maximum path sum of any non-empty path
     */
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN;  // Initialize to minimum to handle all-negative trees
        maxPath(root, maxi);
        return maxi;
    }
    
private:
    /**
     * Helper function to calculate max path sum using post-order traversal
     * @param root: Current node being processed
     * @param maxi: Reference to global maximum path sum
     * @return: Maximum path sum that can be extended upward through this node
     */
    int maxPath(TreeNode* root, int& maxi) {
        // Base case: null node contributes 0
        if (root == NULL)
            return 0;
        
        // Recursively get maximum path sum from left and right subtrees
        // Use max(0, ...) to ignore negative contributions (better to not include them)
        int leftSum = std::max(0, maxPath(root->left, maxi));
        int rightSum = std::max(0, maxPath(root->right, maxi));
        
        // Update global maximum considering the path that:
        // - Comes from left subtree
        // - Includes current node
        // - Goes to right subtree
        // This represents a "turning point" path
        maxi = std::max(maxi, leftSum + rightSum + root->val);
        
        // Return the maximum path sum that can be extended upward
        // Can only choose one direction (left or right) to extend upward
        return root->val + std::max(leftSum, rightSum);
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
    
    // Test Case 1: root = [1,2,3]
    // Tree:     1
    //          / \
    //         2   3
    // Expected output: 6 (path: 2->1->3)
    cout << "Test Case 1:" << endl;
    TreeNode* root1 = newNode(1);
    root1->left = newNode(2);
    root1->right = newNode(3);
    printTree(root1);
    cout << "Maximum Path Sum: " << solution.maxPathSum(root1) << endl;
    cout << "Expected: 6" << endl << endl;
    deleteTree(root1);
    
    // Test Case 2: root = [-10,9,20,null,null,15,7]
    // Tree:       -10
    //            /   \
    //           9     20
    //                /  \
    //               15   7
    // Expected output: 42 (path: 15->20->7)
    cout << "Test Case 2:" << endl;
    TreeNode* root2 = newNode(-10);
    root2->left = newNode(9);
    root2->right = newNode(20);
    root2->right->left = newNode(15);
    root2->right->right = newNode(7);
    printTree(root2);
    cout << "Maximum Path Sum: " << solution.maxPathSum(root2) << endl;
    cout << "Expected: 42" << endl << endl;
    deleteTree(root2);
    
    // Test Case 3: root = [-3]
    // Tree: -3
    // Expected output: -3 (single node)
    cout << "Test Case 3:" << endl;
    TreeNode* root3 = newNode(-3);
    printTree(root3);
    cout << "Maximum Path Sum: " << solution.maxPathSum(root3) << endl;
    cout << "Expected: -3" << endl << endl;
    deleteTree(root3);
    
    // Test Case 4: root = [2,-1]
    // Tree:   2
    //        /
    //      -1
    // Expected output: 2 (single node path)
    cout << "Test Case 4:" << endl;
    TreeNode* root4 = newNode(2);
    root4->left = newNode(-1);
    printTree(root4);
    cout << "Maximum Path Sum: " << solution.maxPathSum(root4) << endl;
    cout << "Expected: 2" << endl << endl;
    deleteTree(root4);
    
    // Test Case 5: root = [5,4,8,11,null,13,4,7,2,null,null,null,1]
    // More complex tree with multiple paths
    cout << "Test Case 5:" << endl;
    TreeNode* root5 = newNode(5);
    root5->left = newNode(4);
    root5->right = newNode(8);
    root5->left->left = newNode(11);
    root5->left->left->left = newNode(7);
    root5->left->left->right = newNode(2);
    root5->right->left = newNode(13);
    root5->right->right = newNode(4);
    root5->right->right->right = newNode(1);
    printTree(root5);
    cout << "Maximum Path Sum: " << solution.maxPathSum(root5) << endl;
    cout << "Expected: 48 (path: 11->4->5->8->13)" << endl << endl;
    deleteTree(root5);
    
    return 0;
}
