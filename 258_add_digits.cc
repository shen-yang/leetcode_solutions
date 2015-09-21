// https://leetcode.com/problems/add-digits/
// Naive solution, note if we convert num to a string then sum the digits, it would 
// be both time and space consuming.

class Solution {
    int SumDigits(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num%10;
            num /= 10;
        }
        return sum;
    }
public:
    int addDigits(int num) {
        while (num >= 10) {
            num = SumDigits(num);
        }
        return num;
    }
};