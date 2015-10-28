// http://lcoj.tk/problems/binary-tree-longest-consecutive-sequencesummer-liu-in_review/

/*
Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections.

Note: The path does not need to go through the root.

For example,
   4
  / \
 1   3
    / \
   2   5
Longest consecutive sequence path is 2-3-4, so return 3.
   5
  / \
 2   3
    / \
   2   4
  / \
 3   1
Longest consecutive sequence path is 1-2-3-4, so return 4.
*/

// For a tree root, a consecutive sequece is either a sequence 
//    1. descending from root or 
//    2. ascending from root or 
//    3. descending from left, ascending from root to right
//    4. descending from right, ascending from root to left

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    int longestConsecutive(TreeNode* root, int* descFromRoot, int* ascFromRoot) {
        if (root == nullptr) {
            *descFromRoot = 0;
            *ascFromRoot = 0;
            return 0;
        }
        
        int descFromLeft = 0, ascFromLeft = 0;
        int num_left = longestConsecutive(root->left, &descFromLeft, &ascFromLeft);
        
        int descFromRight = 0, ascFromRight = 0;
        int num_right = longestConsecutive(root->right, &descFromRight, &ascFromRight);
        
        *descFromRoot = *ascFromRoot = 1;
        if (root->left == nullptr || root->val == root->left->val + 1) 
            *descFromRoot = descFromLeft + 1;
            
        if (root->right == nullptr || root->val == root->right->val + 1)
            *descFromRoot = std::max(*descFromRoot, descFromRight + 1);
        
        if (root->left == nullptr || root->val == root->left->val - 1)
            *ascFromRoot = ascFromLeft + 1;
        
        if (root->right == nullptr || root->val == root->right->val -1)
            *ascFromRoot = std::max(*ascFromRoot, ascFromRight + 1);
        
        int num_root = std::max(std::max(num_left, num_right), 
                                std::max(*ascFromRoot, *descFromRoot));
        
        if (root->left != nullptr && root->right != nullptr && 
            root->val == root->left->val + 1 && root->val == root->right->val - 1) 
            num_root = std::max(num_root, descFromLeft + 1 + ascFromRight);
        
        if (root->left != nullptr && root->right != nullptr &&
            root->val == root->left->val - 1 && root->val == root->right->val + 1)
            num_root = std::max(num_root, ascFromLeft + 1 + descFromRight);
        
        return num_root;
    }
public:
    int longestConsecutive(TreeNode* root) {
        int desc = 0, asc = 0;
        return longestConsecutive(root, &desc, &asc);
    }
};