// https://leetcode.com/problems/move-zeroes/
// Assume the library do minimize assignment operations.

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        auto it = remove(nums.begin(), nums.end(), 0);
        for (; it != nums.end(); ++it) {
            if (*it != 0) {
                *it = 0;
            }
        }
    }
};