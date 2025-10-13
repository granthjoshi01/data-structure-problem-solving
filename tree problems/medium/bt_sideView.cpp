#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/**
 * Binary Tree Right Side View
 * 
 * Problem: Given the root of a binary tree, return the values of the nodes 
 * you can see ordered from top to bottom when looking at the tree from the right side.
 * 
 * Approach: Modified Pre-order Traversal (Root -> Right -> Left)
 * - We traverse the tree level by level, but prioritize the right subtree first
 * - For each level, we only record the first node we encounter (which will be the rightmost)
 * - Time Complexity: O(n) where n is the number of nodes
 * - Space Complexity: O(h) where h is the height of the tree (recursion stack)
 */

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
     * Returns the right side view of the binary tree
     * @param root: Root node of the binary tree
     * @return: Vector containing values visible from the right side
     */
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        recursion(root, 0, result);
        return result;
    }

private:
    /**
     * Helper function to perform modified pre-order traversal
     * @param root: Current node being processed
     * @param level: Current depth level in the tree (0-indexed)
     * @param result: Reference to result vector storing right side view values
     * 
     * Key Insight: By traversing right subtree first and checking if level == result.size(),
     * we ensure only the rightmost node at each level is added to the result.
     */
    void recursion(TreeNode* root, int level, vector<int>& result) {
        // Base case: if node is null, return
        if (root == NULL) return;
        
        // If this is the first node we're visiting at this level,
        // it must be the rightmost node (since we traverse right first)
        if (level == result.size()) {
            result.push_back(root->val);
        }
        
        // Traverse right subtree first to ensure rightmost nodes are processed first
        recursion(root->right, level + 1, result);
        
        // Then traverse left subtree
        recursion(root->left, level + 1, result);
    }
};

/**
 * Helper function to print a vector
 */
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

/**
 * Helper function to delete tree and free memory
 */
void deleteTree(TreeNode* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/**
 * Test function to verify solution
 */
void runTest(int testNum, TreeNode* root, vector<int> expected) {
    Solution solution;
    vector<int> result = solution.rightSideView(root);
    
    cout << "Test Case " << testNum << ": ";
    if (result == expected) {
        cout << "PASSED ✓" << endl;
    } else {
        cout << "FAILED ✗" << endl;
        cout << "  Expected: ";
        printVector(expected);
        cout << "  Got:      ";
        printVector(result);
    }
    cout << "  Output: ";
    printVector(result);
    cout << endl;
}

int main() {
    cout << "Binary Tree Right Side View - Test Cases\n";
    cout << "=========================================\n\n";
    
    // Test Case 1: Standard tree
    // Tree structure:
    //     1
    //    / \
    //   2   3
    //    \   \
    //     5   4
    cout << "Test 1: Standard tree with both left and right children\n";
    TreeNode* test1 = new TreeNode(1);
    test1->left = new TreeNode(2);
    test1->right = new TreeNode(3);
    test1->left->right = new TreeNode(5);
    test1->right->right = new TreeNode(4);
    runTest(1, test1, {1, 3, 4});
    deleteTree(test1);
    
    // Test Case 2: Only right children
    // Tree structure:
    //     1
    //      \
    //       3
    //        \
    //         4
    cout << "Test 2: Tree with only right children\n";
    TreeNode* test2 = new TreeNode(1);
    test2->right = new TreeNode(3);
    test2->right->right = new TreeNode(4);
    runTest(2, test2, {1, 3, 4});
    deleteTree(test2);
    
    // Test Case 3: Only left children
    // Tree structure:
    //     1
    //    /
    //   2
    //  /
    // 3
    cout << "Test 3: Tree with only left children\n";
    TreeNode* test3 = new TreeNode(1);
    test3->left = new TreeNode(2);
    test3->left->left = new TreeNode(3);
    runTest(3, test3, {1, 2, 3});
    deleteTree(test3);
    
    // Test Case 4: Empty tree
    cout << "Test 4: Empty tree (NULL root)\n";
    TreeNode* test4 = nullptr;
    runTest(4, test4, {});
    
    // Test Case 5: Single node
    cout << "Test 5: Single node tree\n";
    TreeNode* test5 = new TreeNode(1);
    runTest(5, test5, {1});
    deleteTree(test5);
    
    // Test Case 6: Complex tree
    // Tree structure:
    //         1
    //        / \
    //       2   3
    //      / \   \
    //     4   5   6
    //    /         \
    //   7           8
    cout << "Test 6: Complex tree with multiple levels\n";
    TreeNode* test6 = new TreeNode(1);
    test6->left = new TreeNode(2);
    test6->right = new TreeNode(3);
    test6->left->left = new TreeNode(4);
    test6->left->right = new TreeNode(5);
    test6->right->right = new TreeNode(6);
    test6->left->left->left = new TreeNode(7);
    test6->right->right->right = new TreeNode(8);
    runTest(6, test6, {1, 3, 6, 8});
    deleteTree(test6);
    
    // Test Case 7: Left-heavy tree that's visible from right
    // Tree structure:
    //       1
    //      /
    //     2
    //      \
    //       3
    //      /
    //     4
    cout << "Test 7: Left-heavy tree with zigzag pattern\n";
    TreeNode* test7 = new TreeNode(1);
    test7->left = new TreeNode(2);
    test7->left->right = new TreeNode(3);
    test7->left->right->left = new TreeNode(4);
    runTest(7, test7, {1, 2, 3, 4});
    deleteTree(test7);
    
    // Test Case 8: Complete binary tree
    // Tree structure:
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7
    cout << "Test 8: Complete binary tree\n";
    TreeNode* test8 = new TreeNode(1);
    test8->left = new TreeNode(2);
    test8->right = new TreeNode(3);
    test8->left->left = new TreeNode(4);
    test8->left->right = new TreeNode(5);
    test8->right->left = new TreeNode(6);
    test8->right->right = new TreeNode(7);
    runTest(8, test8, {1, 3, 7});
    deleteTree(test8);
    
    cout << "\nAll tests completed!\n";
    
    return 0;
}