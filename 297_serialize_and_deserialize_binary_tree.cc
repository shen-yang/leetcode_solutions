// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

// Use level order or preorder traversal to serialize since these two methods 
// saves parents before childs. It would be convenient to deserialize. 

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
    void serialize(const TreeNode* root, string* rep) {
        if (root == nullptr) {
            rep->push_back('#');
            return;
        }
        rep->append(to_string(root->val));
        rep->push_back(' ');
        serialize(root->left, rep);
        serialize(root->right, rep);
    }
    
    TreeNode* deserialize(istringstream& inbuf) {
        char c;
        inbuf >> c;
        if (c == '#') return nullptr;
        else {
            inbuf.putback(c);
            int v;
            inbuf >> v;
            TreeNode* root = new TreeNode(v);
            root->left = deserialize(inbuf);
            root->right = deserialize(inbuf);
            return root;
        }
    }
    
public:

    // Encodes a tree to a single string.
    string serialize(const TreeNode* root) {
        string rep;
        serialize(root, &rep);
        return rep;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const string& data) {
        istringstream inbuf(data);
        return deserialize(inbuf);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));