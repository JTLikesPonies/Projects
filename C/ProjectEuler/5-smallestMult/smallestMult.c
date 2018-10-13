#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

int main() {
    int acc = 1;
    int num = 998001;
    int tempNum = num;

    while(tempNum > 10) {
        acc++;
        tempNum /= 10; }

    int i = acc-1;
    int numArray[acc];
    while(num) {
        numArray[i] = num % 10;
        printf("Num: %d in Array: %d\n", numArray[i], i);
        i--;
        num /= 10; }

    printf("Number of divisions: %d\n", acc); }
