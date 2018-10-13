#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef int bool;
#define true 1
#define false 0


bool isPalindrome(int num) {
    bool palindrome = 0;
    int acc = 1;
    int tempNum = num;

    while(tempNum > 10) {
        acc++;
        tempNum /= 10; }

    int i = acc - 1;
    int numArray[acc];
    while(num) {
        numArray[i] = num % 10;
        i--;
        num /= 10; }

    int j = 0;
    int dist = acc - j;
    while(dist >= 0) {
        if(dist <= 1 && numArray[j] == numArray[acc-1]) {
            palindrome = 1;
            return palindrome; }
        else {
            if(numArray[j] == numArray[acc-1]) {
                j++;
                acc--;
                dist = (acc - 1) - j; }
            else break; }}

    return palindrome; }


int main() {
    int mult;
    int largestMult = 0;

    for(int num1 = 100; num1 <= 999; num1++) {
        for(int num2 = 100; num2 <= 999; num2++) {
            mult = num1 * num2;
            printf("%d * %d =  %d\n", num1, num2, mult);

            if(isPalindrome(mult))
                if(largestMult < mult)
                    largestMult = mult; }}
    //printf("Num1: %d Num2: %d Mult: %d\n",num1, num2, mult);
    printf("Largest palindrome: %d\n", largestMult);
    return 0; }
