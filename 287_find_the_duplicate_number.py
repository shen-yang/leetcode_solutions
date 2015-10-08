# Proof: Use pigeon hole principle.
# If the duplicate is only repeated once, then we could just calculate 
# sum(nums)-sum(range(n)). We need to try other ways.
# The problem requires the complexity to be less than O(n^2). One common 
# complexity is O(nlogn). This brings us to the method of divide and conquer.
# If the array can be modified, just sort it and then scan for the same neighbors.
# Though we can't modify the array, think about sorting it is still inspirational.
# If the array is sorted, it must be something like 1,2,...,k,k,...,k,k+1,...,n.
# There may be no 1 or 2 or k+1 or n because of the duplicate. But the structure
# of the sorted array remains the same. Use the inspirations we get, we may 
# try to think of a divide and conquer method to find k. I tried a binary search
# and succeed! Suppose we have a candidate m, if k > m, then the number of numbers
# larger than m should be larger than n-m. Since the there are total n+1 numbers,
# k > m, then there must be at most m-1 numbers less than m. If k < m, then there
# must be more than m-1 numbers less than m. We could use this condition to branch.

class Solution(object):
    @staticmethod
    def countPart(nums, separator):
        nlarger = 0
        nsmaller = 0
        for v in nums:
            if v > separator:
                nlarger += 1
            elif v < separator:
                nsmaller += 1
        return nlarger, nsmaller
        
    def findDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums) - 1
        end = n
        start = 1
        while start < end:
            mid = start + (end-start)/2
            nlarger, nsmaller = Solution.countPart(nums, mid)
            if nlarger + nsmaller < n:
                return mid
            elif nlarger > n-mid:
                start = mid + 1
            else:
                end = mid - 1
        else:
            return start
            
        