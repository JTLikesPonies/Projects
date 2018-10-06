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
