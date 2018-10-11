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
