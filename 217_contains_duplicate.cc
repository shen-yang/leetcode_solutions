// https://leetcode.com/problems/contains-duplicate/
// The naive version shown as version 1 could get time limit exceeded. Since the 
// problem is a query for the existance. It's easy to come up with a solution using 
// map.

// Version 1
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        size_t n = nums.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};

// Version 2
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> prevs;
        size_t n = nums.size();
        for (size_t i = 0; i < n; ++i) {
            if (prevs.find(nums[i]) != prevs.end()) {
                return true;
            }
            prevs.insert(nums[i]);
        }
        return false;
    }
};