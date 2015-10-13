// https://leetcode.com/problems/ugly-number-ii/
// The next ugly number must be some prior number multiplied by 2, 3 or 5.
// To compute the next number, we multiply the prior numbers by 2, 3 and 5
// respectively, find the first number larger than the current number. Then
// take the minimum of the three numbers as the next number. Since the number
// is growing all the time, we could keep the positions of the the last three
// numbers multiplied by 2, 3 and 5.

/**
 * @param {number} n
 * @return {number}
 */
var nthUglyNumber = function(n) {
    var uglyNumbers = [1];
    
    var total = 1;
    var multipy2 = 0, multiply3 = 0, multiply5 = 0;
    
    while (total < n) {
        var nextNumber = Math.min(uglyNumbers[multipy2]*2, uglyNumbers[multiply3]*3, uglyNumbers[multiply5]*5);
        uglyNumbers.push(nextNumber);
        while (uglyNumbers[multipy2]*2 <= nextNumber) ++multipy2;
        while (uglyNumbers[multiply3]*3 <= nextNumber) ++multiply3;
        while (uglyNumbers[multiply5]*5 <= nextNumber) ++multiply5;
        ++total;
    }
    
    return uglyNumbers.pop();
};