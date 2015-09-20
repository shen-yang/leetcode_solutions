// Naive solution would first sort the numbers, then find the maximum gap.
// But there is a better solution: use the pigeonhole principle.
// Suppose the sorted sequence of arguments are a1, a2, ..., an.
// There are n-1 gaps and the accumulated gap is an-a1. The average gap is
// (an-a1)/(n-1). By the pigeonhole principle, the maximum gap is greater or
// equal to the average. We could assign the numbers into n buckets [a1, a1+avg),
// [a1+avg, a1+avg*2), ..., [a1+avg*(n-2), a1+avg*(n-1)), [an, an + avg).
// The maximum gap can't be between two numbers in the same bucket. It must be the
// maximum difference between the maximum of a lower bucket and the next minimum 
// of a higher bucket. Note the two buckets may not be consecutive because there
// may be empty bucket.

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        size_t n = nums.size();
        if (n < 2) return 0;
        int maxi = *max_element(nums.begin(), nums.end());
        int mini = *min_element(nums.begin(), nums.end());
		int total_gap = maxi - mini;
        if (total_gap == 0) { //we need to divide total_gap later
            return 0;
        }
        
        vector<int> range_max(n, -1);
        vector<int> range_min(n, INT_MAX);
        for (size_t i = 0; i < n; ++i) {
			// The following statement is actually average=total_gap/(n-1), then (nums[i]-mini)/average
			// I write it as it is to avoid possible precision problems.
            int index = static_cast<long long>(nums[i]-mini)*(n-1)/total_gap;
            range_max[index] = std::max(range_max[index], nums[i]);
            range_min[index] = std::min(range_min[index], nums[i]);
        }
        
        int max_gap = 0, last = 0;
        for (size_t i = 1; i < n; ++i) {
            if (range_max[i] == -1) {
                continue;
            }
            max_gap = std::max(range_min[i]-range_max[last], max_gap);
            last = i;
        }
        
        return max_gap;
    }
};