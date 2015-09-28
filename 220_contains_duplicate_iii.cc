// https://leetcode.com/problems/contains-duplicate-iii/
// It may helps first omit the condition |i-j|<=k. That is, only consider the
// problem: whether there exists two numbers differ at most t. It turns out 
// straightforward that we need a ordered data structure to store the visited
// elements and query the range [nums[i]-t, nums[i]+t]. nums[i] is the current
// number being considered. Then we add the condition previously omitted. Now
// we also need the indices for the numbers visited. So we use map in STL.
// Note the solution marked with version 1 could fail at ([0,INT_MAX], 1, INT_MAX)
// because of overflow. We could change the condition 'itr->first <= nums[i] + t'
// to 'itr->first - nums[i] <= t'. But still have overflow problem for other case
// like nums[i]-t is smaller than INT_MIN. The more easier and secure solution 
// is to use long lont instead of int, which is shown as version 2.
// Version 3 is a very clever solution using bucket. We partition numbers into 
// groups so that any two numbers in the same partition differ at most t. Then the 
// possible candidate could only be in the same group or in the neighbors.

// Version 1
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        map<int, size_t> value_index_map;
        for (size_t i = 0; i < nums.size(); ++i) {
            auto itr = value_index_map.lower_bound(nums[i]-t);
            while (itr != value_index_map.end() && itr->first <= nums[i] + t) {
                if (i-itr->second <= k) {
                    return true;
                }
                ++itr;
            }
            value_index_map[nums[i]] = i;
        }
        return false;
    }
};

// Version 2
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        typedef long long ll;
        map<ll, size_t> value_index_map;
        for (size_t i = 0; i < nums.size(); ++i) {
            ll ni = nums[i];
            auto itr = value_index_map.lower_bound(ni-t);
            while (itr != value_index_map.end() && itr->first <= ni + t) {
                if (i-itr->second <= k) {
                    return true;
                }
                ++itr;
            }
            value_index_map[nums[i]] = i;
        }
        return false;
    }
};

// Version 3
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        map<int, int> buckets;
        for (size_t i = 0; i < nums.size(); ++i) {
            long long ni = nums[i]; // overflow at [-1,2147483647],1,2147483647 if we
									// only use int
            int nbucket = t == 0? ni : ni/t;
            int offset = t == 0? 0 : 1;
            for (int b = nbucket-offset; b <= nbucket+offset; ++b) {
                auto itr = buckets.find(b);
                if (itr != buckets.end() && abs(itr->second-ni) <= t) {
                    return true;
                }
            }
            buckets[nbucket] = ni; // we are sure slot nbucket has no element, 
								   // else already return true in above code.
            if (buckets.size() > k) {
                buckets.erase(nums[i-k]/max(t,1));
            }
        }
        return false;
    }
};