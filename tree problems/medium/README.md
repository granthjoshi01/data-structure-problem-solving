

Collection of medium-difficulty tree problems with optimized solutions.

## Problems

| Problem | Topics | Time | Space | Status |
|---------|--------|------|-------|--------|
| [Vertical Order Traversal](vertical_order_traversal.cpp) | BFS, Map | O(N log N) | O(N) | ✅ |
| [Boundary Traversal](boundary_traversal.cpp) | DFS | O(N) | O(H) | ✅ |
| [Lowest Common Ancestor](lowest_common_ancestor.cpp) | Recursion | O(N) | O(H) | ⏳ |
| [Zigzag Level Order](zigzag_traversal.cpp) | BFS | O(N) | O(N) | ⏳ |
| [Right Side View](right_side_view.cpp) | BFS/DFS | O(N) | O(H) | ⏳ |
| [Path Sum II](path_sum_ii.cpp) | Backtracking | O(N) | O(H) | ⏳ |

**Legend:** ✅ Completed | ⏳ In Progress

## Key Concepts

- **Advanced Traversals**: Vertical, Boundary, Zigzag
- **View Problems**: Left/Right/Top/Bottom views
- **Path Finding**: DFS with backtracking
- **Tree Construction**: From multiple traversals

## Quick Tips

**BFS vs DFS?**
- BFS: Level-order, shortest path, views
- DFS: All paths, path sums, depth problems

**Common Patterns:**
```cpp
// Coordinate tracking
map<int, map<int, multiset<int>>>

// Level order with state
queue<pair<TreeNode*, int>>
```

---

**Last Updated:** October 2025 | **Progress:** 2/6 completed
