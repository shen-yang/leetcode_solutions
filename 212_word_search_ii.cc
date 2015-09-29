// https://leetcode.com/problems/word-search-ii/
// Assume we have already done problem 79: word search and problem 208: implement trie.
// Now we still use the DFS method as in problem 79. But this time we need to test 
// prefix of a set of words to terminate the search as early as possible. Trie is a
// perfect fit. Version 1 use this method.

// Version 2 and 3 get time limit exceeded. But they still provide other ways to consider.
// Version 2 does an exhaustive search.
// Version 3 maintains a set of the current matching word to try early termination of 
// the search. This is similar to NFA in regular expression, which we maintain a set 
// of current matching states.

// Version 1
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
    void Insert(const string& word) {
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
    bool Search(const string& word) const{
        TrieNode* p = NodeAfterPrefix(word);
        return p != nullptr && p->is_node_;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool StartsWith(const string& prefix) const{
        TrieNode* p = NodeAfterPrefix(prefix);
        return p != nullptr;
    }
    
    ~Trie() {
        DeleteNodes(root_);
    }

private:
    TrieNode* NodeAfterPrefix(const string& prefix) const{
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

class Solution {
    void dfs(const vector<vector<char> >& board,
             int r, int c,
			 const Trie& wset,
			 vector<vector<bool> >* visited,
			 string* word,
			 unordered_set<string>* rset) {
        (*visited)[r][c] = true;
        word->push_back(board[r][c]);
		if (wset.StartsWith(*word)) {
		    if (wset.Search(*word)) {
		        rset->insert(*word);
		    }
			int offr[] = {0, -1, 0, 1};
			int offc[] = {-1, 0, 1, 0};
			for (int i = 0; i < 4; ++i) {
				int nr = r + offr[i];
				int nc = c + offc[i];
				if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size() && !(*visited)[nr][nc]) {
					dfs(board, nr, nc, wset, visited, word, rset);
				}
			}
		}
		word->pop_back();
        (*visited)[r][c] = false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        size_t nrows = board.size();
        if (nrows == 0) return result;
        size_t ncols = board[0].size();
        vector<vector<bool> > visited(nrows, vector<bool>(ncols, false));
        string word;
        unordered_set<string> rset;
        Trie wset;
        for (auto& s: words) {
            wset.Insert(s);
        }
        for (int r = 0; r < nrows; ++r) {
            for (int c = 0; c < ncols; ++c) {
                dfs(board, r, c, wset, &visited, &word, &rset);
            }
        }
        result.assign(rset.begin(), rset.end());
        return result;
    }
};

// Version 2
class Solution {
    void dfs(const vector<vector<char> >& board,
             const unordered_set<string>& wset,
             int r, int c, vector<vector<bool> >* visited,
             string* word, unordered_set<string>* rset) {
        (*visited)[r][c] = true;
        word->push_back(board[r][c]);
        int offr[] = {0, -1, 0, 1};
        int offc[] = {-1, 0, 1, 0};
        for (int i = 0; i < 4; ++i) {
            int nr = r + offr[i];
            int nc = c + offc[i];
            if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size() && !(*visited)[nr][nc]) {
                dfs(board, wset, nr, nc, visited, word, rset);
            }
        }
        if (wset.find(*word) != wset.end()) {
            rset->insert(*word);
        }
        word->pop_back();
        (*visited)[r][c] = false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        size_t nrows = board.size();
        if (nrows == 0) return result;
        size_t ncols = board[0].size();
        unordered_set<string> wset(words.begin(), words.end());
        vector<vector<bool> > visited(nrows, vector<bool>(ncols, false));
        string word;
        unordered_set<string> rset;
        for (int r = 0; r < nrows; ++r) {
            for (int c = 0; c < ncols; ++c) {
                dfs(board, wset, r, c, &visited, &word, &rset);
            }
        }
        result.assign(rset.begin(), rset.end());
        return result;
    }
}; 

//Version 3
class Solution {
	struct Slice{
		Slice(){}
		Slice(const char* s, const char* pos): s_(s), pos_(pos){}
		const char* s_;
		const char* pos_;
	};
    void dfs(const vector<vector<char> >& board,
             int r, int c,
			 const vector<Slice>& wset,
			 vector<vector<bool> >* visited,
			 unordered_set<string>* rset) {
        (*visited)[r][c] = true;
		vector<Slice> nwset;
        for (size_t i = 0; i < wset.size(); ++i) {
			if (*wset[i].pos_ == board[r][c]) {
				Slice ns(wset[i].s_, wset[i].pos_+1);
				if (*ns.pos_ == '\0') {
					rset->insert(ns.s_);
				} else {
					nwset.push_back(ns);
				}
			}
		}
		if (!nwset.empty()) {
			int offr[] = {0, -1, 0, 1};
			int offc[] = {-1, 0, 1, 0};
			for (int i = 0; i < 4; ++i) {
				int nr = r + offr[i];
				int nc = c + offc[i];
				if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size() && !(*visited)[nr][nc]) {
					dfs(board, nr, nc, nwset, visited, rset);
				}
			}
		}
        (*visited)[r][c] = false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        size_t nrows = board.size();
        if (nrows == 0) return result;
        size_t ncols = board[0].size();
        vector<vector<bool> > visited(nrows, vector<bool>(ncols, false));
        string word;
        unordered_set<string> rset;
        for (int r = 0; r < nrows; ++r) {
            for (int c = 0; c < ncols; ++c) {
				vector<Slice> wset(words.size());
				for (size_t i = 0; i < words.size(); ++i) {
					wset[i] = Slice(words[i].c_str(), words[i].c_str());
				}
                dfs(board, r, c, wset, &visited, &rset);
            }
        }
        result.assign(rset.begin(), rset.end());
        return result;
    }
};  