/*
 *  The sum of the squares of the first ten natural numbers is,
 *  1^2 + 2^2 + ... + 10^2 = 385
 *
 *  The square of the sum of the first ten natural numbers is,
 *  (1 + 2 + ... + 10)^2 = 552 = 3025
 *
 *  Hence the difference between the sum of the squares of the
 *  first ten natural numbers and the square of the sum is
 *  3025 − 385 = 2640.
 *
 *  Find the difference between the sum of the squares of the
 *  first one hundred natural numbers and the square of the sum.
 */

#include <stdio.h>

int main() {
    int sqSum = 0;
    int sumSq = 0;
    int diff;

    for(int j = 1; j < 101; j++)
        sumSq += j * j;

    for(int i = 1; i < 101; i++)
        sqSum += i;
    sqSum *= sqSum;

    diff = sqSum - sumSq;

    printf("Difference: %d\n", diff);

    return 0; }
