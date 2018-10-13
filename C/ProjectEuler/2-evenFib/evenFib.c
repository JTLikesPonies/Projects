/*
 *  Each new term in the Fibonacci sequence is generated
 *  by adding the previous two terms. By starting with 1
 *  and 2, the first 10 terms will be:
 *
 *      1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
 *
 *  By considering the terms in the Fibonacci sequence
 *  whose values do not exceed four million, find the sum
 *  of the even-valued terms.
 */

#include <stdio.h>

#define maxNum 4000000

int main() {
    int firstNum = 1;
    int secNum = 2;
    long fibNum = 0;
    long sum = 2;
    printf("%d\n%d\n", firstNum, secNum);

    while(fibNum < maxNum) {
        fibNum = firstNum + secNum;
        firstNum = secNum;
        secNum = fibNum;
        if(fibNum % 2 == 0) {
            printf("%ld\n", fibNum);
            sum += fibNum; }}

    printf("Sum: %ld\n", sum);
    return 0; }
