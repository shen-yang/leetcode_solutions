// https://leetcode.com/problems/contains-duplicate-ii/
// Compared to 'contains duplicate i', now we also need to know the index of number for 
// query. So we use a number to index map.

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, size_t> value_index_map;
        for (size_t i = 0; i < nums.size(); ++i) {
            auto itr = value_index_map.find(nums[i]);
            if (itr != value_index_map.end() && i - itr->second <= k) {
                return true;
            }
            value_index_map[nums[i]] = i;
        }
        return false;
    }
};