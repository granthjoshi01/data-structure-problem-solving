
Advanced tree problems requiring complex algorithms and optimization techniques.

## Problems

| Problem | Topics | Time | Space | Status |
|---------|--------|------|-------|--------|
| [Binary Tree Maximum Path Sum](bt_maxPathSum.cpp) | DFS, Recursion | O(N) | O(H) | 
| [Vertical Order Traversal](verticalTravers.cpp) | BFS, Map, Sorting | O(N log N) | O(N) | 



## Key Concepts

- **Path Sum Problems**: Calculate maximum/minimum paths through tree
- **Global vs Local Optimization**: Track both node-to-node and root-to-node paths
- **Complex Traversals**: Multi-dimensional tracking with sorting requirements
- **Edge Cases**: Negative values, single nodes, skewed trees

## Common Patterns

```cpp
// Global variable for path sum
int maxSum = INT_MIN;

// Post-order DFS for path calculation
int dfs(TreeNode* node) {
    // Base case + recursive logic
}

// Coordinate-based traversal
map<int, map<int, multiset<int>>> nodes;
queue<pair<TreeNode*, pair<int, int>>> q;
```

## Key Challenges

**Maximum Path Sum:**
- Handle negative values correctly
- Differentiate between path through node vs path ending at node
- Update global maximum while returning local maximum

**Vertical Traversal:**
- Implement proper coordinate system (x, y)
- Sort nodes at same position correctly
- Handle tie-breaking rules efficiently



---

**Last Updated:** October 2025 | **Progress:** 2/2 completed 🎉
