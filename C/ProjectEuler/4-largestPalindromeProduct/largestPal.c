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
    while(dist >= 1) {
        if(dist <= 1) {
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
    int num1 = 99;
    int num2 = 99;
    bool isNotPalindrome = 1;
    int mult, largestMult;

    for(num1; num1 > 99; num1--) {
        for(num2; num2 > 99; num2--) {
            mult = num1 * num2;
            printf("%d * %d =  %d\n", num1, num2, mult);

            if(isPalindrome(mult)) {
                if(largestMult < mult)
                    largestMult = mult; }}}

    printf("Largest palindrome: %d\n", largestMult);
    return 0; }
