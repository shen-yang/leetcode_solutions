// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// We could do a depth first traversal. If p and q meet at a node the first time,
// then that's the LCA. To achive this goal, if p or q is in subtree, we need 
// subtree traversal tell us that information. In my code, I just return p or q. 
// Also, we also need to store the result when p and q first meet. In my code, 
// I use another pointer parameter to pass out the result. You could store it as 
// a member if you care the stack space.
// Actually the code can also be applied to binary tree. I can't see the use of 
// the BST condition.

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
    // return p if subtree rooted at root contains p;
	//        q if subtree rooted at root contains p;
	//        lca if subtree rooted at root contains both p and q;
	//        nullptr otherwise.
	// The first time p and q meet, we set ancestor. Note this is necessary because
	// if we return p, we cannot distinguish whether p is ancestor of q or q 
	// doesn't exist at all.
    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode** ancestor) {
        if (root == nullptr) {
            return nullptr;
        }
        if (*ancestor != nullptr) {
            return *ancestor;
        }
        TreeNode* left_lca = LCA(root->left, p, q, ancestor);
        TreeNode* right_lca = LCA(root->right, p, q, ancestor);
        bool hasp = left_lca == p || right_lca == p || root == p;
        bool hasq = left_lca == q || right_lca == q || root == q;
        if (hasp && hasq) {
            *ancestor = root;
            return root;
        } else {
            TreeNode* ret = left_lca != nullptr? left_lca: right_lca;
            if (ret != nullptr) {
                return ret;
            } else {
                return (root == p || root == q)? root: nullptr;
            }
        }
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ancestor = nullptr;
        LCA(root, p, q, &ancestor);
        return ancestor;
    }
};

// Or if we are assured p and q exist in tree, the code could be much simplified.
// We don't need the extra ancestor now. And we don't need to distinguish whether p // is an ancestor of q or we just meet p. The logical code could be very simple.
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        
        TreeNode* left_lca = lowestCommonAncestor(root->left, p, q);
        TreeNode* right_lca = lowestCommonAncestor(root->right, p, q);
        
        if (left_lca != nullptr && right_lca != nullptr) {
            return root;
        }
        return left_lca == nullptr? right_lca: left_lca;
    }
};