// https://leetcode.com/problems/word-search/
// Using a DFS solution, stop as early as possible.

class Solution {
    bool dfs(const vector<vector<char> > &board, 
             int r, int c, 
             const char* word,
             vector<vector<bool> >* visited){
        if (*word != board[r][c]) {
            return false;
        }
        if (*(word+1) == '\0') {
            return true;
        }
        (*visited)[r][c] = true;
        int offr[] = {0, -1, 0, 1};
        int offc[] = {-1, 0, 1, 0};
        for (int i = 0; i < 4; ++i) {
            int nr = r + offr[i];
            int nc = c + offc[i];
            if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size() && !(*visited)[nr][nc]) {
                if (dfs(board, nr, nc, word+1, visited)) {
                    return true;
                }
            }
        }
        (*visited)[r][c] = false;
        
        return false;
    }
public:
    bool exist(vector<vector<char> > &board, string word) {
        int nrows = board.size();
        if (nrows == 0) return false;
        int ncols = board[0].size();
        if (ncols == 0) return false;

        vector<vector<bool> > visited(nrows, vector<bool>(ncols, false));
        for (int r = 0; r < nrows; ++r) {
            for (int c = 0; c < ncols; ++c) {
                if (dfs(board, r, c, word.c_str(), &visited)) {
                    return true;
                }
            }
        }
        return false;
    }
};