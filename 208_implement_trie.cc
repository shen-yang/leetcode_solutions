// Common implementation. Note below I add a NodeAfterPrefix to remove duplicate code
// in search and startsWith. I also add a ~Trie() destructor to prevent memory leak.
// Since the interface of Trie doesn't need to expose TrieNode, it's actually better
// to implement TrieNode as a inner class of Trie.

class TrieNode {
    static const int kNumChar = 26;
    TrieNode* successors[kNumChar];
    bool is_node_;
    friend class Trie;
public:
    // Initialize your data structure here.
    TrieNode(): is_node_(false) {
        fill(successors, successors + kNumChar, nullptr);
    }
};

class Trie {
public:
    Trie(): root_(new TrieNode) {}

    // Inserts a word into the trie.
    void insert(const string& word) {
        TrieNode* current = root_;
        for (char c: word) {
            if (current->successors[c-'a'] == nullptr) {
                current->successors[c-'a'] = new TrieNode;
            }
            current = current->successors[c-'a'];
        }
        current->is_node_ = true;
    }

    // Returns if the word is in the trie.
    bool search(const string& word) {
        TrieNode* p = NodeAfterPrefix(word);
        return p != nullptr && p->is_node_;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(const string& prefix) {
        TrieNode* p = NodeAfterPrefix(prefix);
        return p != nullptr;
    }
    
    ~Trie() {
        DeleteNodes(root_);
    }

private:
    TrieNode* NodeAfterPrefix(const string& prefix) {
        TrieNode* current = root_;
        for (char c: prefix) {
            if (current->successors[c-'a'] == nullptr) {
                return nullptr;
            }
            current = current->successors[c-'a'];
        }
        return current;
    }
    void DeleteNodes(TrieNode* n) {
        for (int i = 0; i < TrieNode::kNumChar; ++i) {
            if (n->successors[i] != nullptr) {
                DeleteNodes(n->successors[i]);
            }
        }
        delete n;
    }
    TrieNode* root_;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");