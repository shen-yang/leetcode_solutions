// https://leetcode.com/problems/move-zeroes/
// Only those assignment necessary are made. We test *it != 0 and *first != 0
// to avoid unnecessary assignments.

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        auto first = find(nums.begin(), nums.end(), 0);
        for (auto it = first; it != nums.end(); ++it) {
            if (*it != 0 && it != first) {
                *first++ = *it;
            }
        }
        for (; first != nums.end(); ++first) {
            if (*first != 0) {
                *first = 0;
            }
        }
    }
};