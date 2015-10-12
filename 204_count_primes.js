// https://leetcode.com/problems/count-primes/
// Naive implementation could test for every number's primality.
// That is, for each number n, test any of 2, 3, ..., sqrt(n) can
// be divided by n. The complexity is O(sum(sqrt(n)) = O(n^(3/2)).
// This method will exceed time limit of the oj.
// An ancient algorithm called the sieve of Eratosthenes could also 
// be applied here. The complexity is O(nlglgn).
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

// Naive primality test
/**
 * @param {number} n
 * @return {number}
 */
var countPrimes = function(n) {
    var isPrime = function(n) {
        for (var i = 2; i*i <= n; ++i) {
            if (n % i === 0)
                return false;
        }
        return n != 1;
    };
    var count = 0;
    for (var i = 2; i < n; ++i)
        count += isPrime(i);
    return count;
};

// the sieve of Eratosthenes
var countPrimes = function(n) {
    var isPrime = new Array(n);
    isPrime[0] = isPrime[1] = false;
    isPrime.fill(true, 2);
    for (var i = 2; i*i < n; ++i) {
        if (isPrime[i]) {
            for (var j = i*i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    var count = isPrime.reduce(
        function(previousValue, currentValue) {
            return previousValue + currentValue;
        }, 0);
    return count;
};