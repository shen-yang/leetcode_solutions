// https://leetcode.com/problems/add-digits/
// Smarter solution. Note eventually we want a digit, that is, one of 0-9.
// And recall that the number theory says that num % 9 = sum(digits of num) % 9. 
// We could do this recursively. For example, 156 % 9 = (1+5+6 = 12) % 9 = (1+2) % 9.
// We just need to compute 156 % 9;)

class Solution {
public:
    int addDigits(int num) {
        if (num == 0) {
            return 0;
        }
        int m = num % 9;
        if (m == 0) {
            return 9;
        } else {
            return m;
        }     
    }
};