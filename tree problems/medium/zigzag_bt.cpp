/**
 * Binary Tree Zigzag Level Order Traversal
 * 
 * Problem: Given the root of a binary tree, return the zigzag level order 
 * traversal of its nodes' values (i.e., from left to right, then right to 
 * left for the next level and alternate between).
 * 
 * Example:
 * Input:
 *       3
 *      / \
 *     9  20
 *       /  \
 *      15   7
 * Output: [[3], [20,9], [15,7]]
 * 
 * Time Complexity: O(n) where n is the number of nodes
 * Space Complexity: O(n) for the queue and result storage
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        
        // Handle empty tree
        if (root == NULL)
            return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);  // Pre-allocate vector with size
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Calculate index based on direction
                int index = (leftToRight) ? i : (size - 1 - i);
                level[index] = node->val;
                
                // Add children to queue for next level
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            
            // Toggle direction after completing each level
            leftToRight = !leftToRight;
            result.push_back(level);
        }
        
        return result;
    }
};

// Helper function to create a new tree node
TreeNode* newNode(int val) {
    return new TreeNode(val);
}

// Helper function to print 2D vector
void print2DVector(const vector<vector<int>>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << "[";
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j];
            if (j < vec[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < vec.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

// Main function with test cases
int main() {
    Solution solution;
    
    // Test Case 1
    cout << "Test Case 1:" << endl;
    cout << "Tree structure:" << endl;
    cout << "      3" << endl;
    cout << "     / \\" << endl;
    cout << "    9  20" << endl;
    cout << "      /  \\" << endl;
    cout << "     15   7" << endl;
    
    TreeNode* root1 = newNode(3);
    root1->left = newNode(9);
    root1->right = newNode(20);
    root1->right->left = newNode(15);
    root1->right->right = newNode(7);
    
    vector<vector<int>> result1 = solution.zigzagLevelOrder(root1);
    cout << "Output: ";
    print2DVector(result1);
    cout << "Expected: [[3],[20,9],[15,7]]" << endl << endl;
    
    // Test Case 2
    cout << "Test Case 2:" << endl;
    cout << "Tree structure:" << endl;
    cout << "      1" << endl;
    
    TreeNode* root2 = newNode(1);
    vector<vector<int>> result2 = solution.zigzagLevelOrder(root2);
    cout << "Output: ";
    print2DVector(result2);
    cout << "Expected: [[1]]" << endl << endl;
    
    // Test Case 3
    cout << "Test Case 3:" << endl;
    cout << "Tree structure: Empty" << endl;
    
    TreeNode* root3 = nullptr;
    vector<vector<int>> result3 = solution.zigzagLevelOrder(root3);
    cout << "Output: ";
    print2DVector(result3);
    cout << "Expected: []" << endl << endl;
    
    // Test Case 4
    cout << "Test Case 4:" << endl;
    cout << "Tree structure:" << endl;
    cout << "        1" << endl;
    cout << "       / \\" << endl;
    cout << "      2   3" << endl;
    cout << "     / \\" << endl;
    cout << "    4   5" << endl;
    
    TreeNode* root4 = newNode(1);
    root4->left = newNode(2);
    root4->right = newNode(3);
    root4->left->left = newNode(4);
    root4->left->right = newNode(5);
    
    vector<vector<int>> result4 = solution.zigzagLevelOrder(root4);
    cout << "Output: ";
    print2DVector(result4);
    cout << "Expected: [[1],[3,2],[4,5]]" << endl << endl;
    
    return 0;
}