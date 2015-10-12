// https://leetcode.com/problems/perfect-squares/
// First thought: try all possibilities. 
// numSqr(n) = min(1 + numSquares(n-1), 4 + numSquares(n-4), ..., 
// 1 + numSquares(n-sqrt(n)*sqrt(n)) ). And note that this could be
// solved by dynamic programming.

/**
 * @param {number} n
 * @return {number}
 */
var numSquares = function(n) {
    var numSqr = new Array(n+1);
    numSqr[0] = 0;
    for (var i = 1; i <= n; ++i) {
        numSqr[i] = i;
        for (var j = 1; j*j <= i; ++j) {
            numSqr[i] = Math.min(numSqr[i-j*j]+1, numSqr[i]);
        }
    }
    return numSqr[n];
};