/*
 *  If we list all the natural numbers below 10 that are
 *  multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of
 *  these multiples is 23.
 *
 *  Find the sum of all the multiples of 3 or 5 below 1000.
 */


#include <stdio.h>

int main() {
    int numList[1000];
    int sum = 0;

    for(int i = 0; i < 1000; i++) {
        numList[i] = i;
        if(numList[i] % 3 == 0 || numList[i] % 5 == 0) {
            printf("%d\n",numList[i]);
            sum += numList[i]; }}

    printf("Sum: %d\n", sum);
    return 0; }
