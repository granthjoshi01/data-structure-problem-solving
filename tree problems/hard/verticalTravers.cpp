/**
 * Vertical Order Traversal of Binary Tree
 * 
 * Problem: Given the root of a binary tree, return the vertical order traversal 
 * of its nodes' values. (i.e., from top to bottom, column by column).
 * 
 * If two nodes are in the same row and column, the order should be from left to right.
 * 
 * Time Complexity: O(N log N) - N nodes, sorting at each position
 * Space Complexity: O(N) - storing all nodes
 * 
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

/**
 * Definition for a binary tree node.
 */
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
    /**
     * Performs vertical order traversal of a binary tree
     * 
     * Algorithm:
     * 1. Use BFS (level order traversal) with coordinate tracking
     * 2. Each node gets (x, y) coordinates where:
     *    - x: horizontal distance (column) - left is negative, right is positive
     *    - y: vertical distance (row) - increases going down
     * 3. Store nodes in map: column -> row -> multiset of values
     * 4. Multiset automatically sorts values at same position
     * 5. Build result by iterating columns left to right
     * 
     * @param root: Root node of the binary tree
     * @return: 2D vector containing vertical order traversal
     */
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // Handle empty tree
        if (!root) return {};
        
        // Map structure: x-coordinate -> y-coordinate -> multiset of node values
        // multiset keeps values sorted at same position
        map<int, map<int, multiset<int>>> nodes;
        
        // Queue for BFS: stores {node, {x-coordinate, y-coordinate}}
        queue<pair<TreeNode*, pair<int, int>>> todo;
        
        // Start with root at origin (0, 0)
        todo.push({root, {0, 0}});
        
        // BFS traversal
        while (!todo.empty()) {
            auto p = todo.front();
            todo.pop();
            
            TreeNode* node = p.first;
            int x = p.second.first;   // column (horizontal position)
            int y = p.second.second;  // row (vertical position)
            
            // Insert node value into corresponding position
            nodes[x][y].insert(node->val);
            
            // Add left child: move left (x-1) and down (y+1)
            if (node->left) {
                todo.push({node->left, {x - 1, y + 1}});
            }
            
            // Add right child: move right (x+1) and down (y+1)
            if (node->right) {
                todo.push({node->right, {x + 1, y + 1}});
            }
        }
        
        // Build the final result
        vector<vector<int>> answer;
        
        // Iterate through columns from left to right (map is automatically sorted)
        for (auto p : nodes) {
            vector<int> col;
            
            // For each column, iterate through rows top to bottom
            for (auto q : p.second) {
                // Insert all values at this position (already sorted in multiset)
                col.insert(col.end(), q.second.begin(), q.second.end());
            }
            
            answer.push_back(col);
        }
        
        return answer;
    }
};

// ==================== UTILITY FUNCTIONS FOR TESTING ====================

/**
 * Helper function to create a sample tree for testing
 */
TreeNode* createSampleTree1() {
    /*
     * Tree structure:
     *         3
     *        / \
     *       9   20
     *          /  \
     *         15   7
     */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createSampleTree2() {
    /*
     * Tree structure:
     *         1
     *        / \
     *       2   3
     *      / \ / \
     *     4  5 6  7
     */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createSampleTree3() {
    /*
     * Tree structure with duplicates at same position:
     *         1
     *        / \
     *       2   3
     *      / \
     *     4   6
     *        /
     *       5
     */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(6);
    root->left->right->left = new TreeNode(5);
    return root;
}

/**
 * Helper function to print the result
 */
void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

/**
 * Helper function to clean up tree memory
 */
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ==================== MAIN FUNCTION WITH TEST CASES ====================

int main() {
    Solution solution;
    
    cout << "=== Vertical Order Traversal Test Cases ===" << endl << endl;
    
    // Test Case 1
    cout << "Test Case 1:" << endl;
    cout << "Tree:         3" << endl;
    cout << "            /   \\" << endl;
    cout << "           9    20" << endl;
    cout << "               /  \\" << endl;
    cout << "              15   7" << endl;
    TreeNode* root1 = createSampleTree1();
    vector<vector<int>> result1 = solution.verticalTraversal(root1);
    cout << "Output: ";
    printResult(result1);
    cout << "Expected: [[9],[3,15],[20],[7]]" << endl << endl;
    deleteTree(root1);
    
    // Test Case 2
    cout << "Test Case 2:" << endl;
    cout << "Tree:         1" << endl;
    cout << "            /   \\" << endl;
    cout << "           2     3" << endl;
    cout << "          / \\   / \\" << endl;
    cout << "         4   5 6   7" << endl;
    TreeNode* root2 = createSampleTree2();
    vector<vector<int>> result2 = solution.verticalTraversal(root2);
    cout << "Output: ";
    printResult(result2);
    cout << "Expected: [[4],[2],[1,5,6],[3],[7]]" << endl << endl;
    deleteTree(root2);
    
    // Test Case 3
    cout << "Test Case 3 (with sorting at same position):" << endl;
    cout << "Tree:         1" << endl;
    cout << "            /   \\" << endl;
    cout << "           2     3" << endl;
    cout << "          / \\" << endl;
    cout << "         4   6" << endl;
    cout << "            /" << endl;
    cout << "           5" << endl;
    TreeNode* root3 = createSampleTree3();
    vector<vector<int>> result3 = solution.verticalTraversal(root3);
    cout << "Output: ";
    printResult(result3);
    cout << "Expected: [[4],[2],[1,5,6],[3]]" << endl;
    cout << "Note: 5 and 6 are at same position, so sorted order" << endl << endl;
    deleteTree(root3);
    
    // Edge Case: Single Node
    cout << "Test Case 4 (Single Node):" << endl;
    TreeNode* root4 = new TreeNode(1);
    vector<vector<int>> result4 = solution.verticalTraversal(root4);
    cout << "Output: ";
    printResult(result4);
    cout << "Expected: [[1]]" << endl << endl;
    deleteTree(root4);
    
    // Edge Case: Empty Tree
    cout << "Test Case 5 (Empty Tree):" << endl;
    vector<vector<int>> result5 = solution.verticalTraversal(nullptr);
    cout << "Output: ";
    printResult(result5);
    cout << "Expected: []" << endl << endl;
    
    cout << "=== All Test Cases Completed ===" << endl;
    
    return 0;
}

/*
==================== COMPLEXITY ANALYSIS ====================

Time Complexity: O(N log N)
- O(N) for BFS traversal visiting all N nodes
- O(log N) for inserting into multiset at each node
- Total: O(N log N)

Space Complexity: O(N)
- O(N) for the map storing all nodes
- O(N) for the queue in worst case (complete tree)
- O(N) for the result vector
- Total: O(N)

==================== KEY INSIGHTS ====================

1. Coordinate System:
   - x (column): left child = parent_x - 1, right child = parent_x + 1
   - y (row): child_y = parent_y + 1

2. Data Structure Choice:
   - map<int, ...>: automatically sorts by column (x-coordinate)
   - map<int, multiset<int>>: sorts by row, then by value
   - multiset: handles duplicates and keeps them sorted

3. Why multiset instead of vector?
   - Nodes at same (x, y) position need to be sorted
   - multiset automatically maintains sorted order

4. Interview Tips:
   - Start by explaining the coordinate system
   - Mention why you chose map and multiset
   - Walk through a small example
   - Discuss edge cases (empty tree, single node)

==================== RELATED PROBLEMS ====================

1. Binary Tree Level Order Traversal (LeetCode 102)
2. Binary Tree Zigzag Level Order Traversal (LeetCode 103)
3. Binary Tree Right Side View (LeetCode 199)
4. Boundary Traversal of Binary Tree (Medium)
5. Diagonal Traversal of Binary Tree (Medium)

*/