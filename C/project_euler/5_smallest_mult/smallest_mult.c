/*
 *  2520 is the smallest number that can be
 *  divided by each of the numbers from 1 to
 *  10 without any remainder.
 *
 *  What is the smallest positive number that
 *  is evenly divisible by all of the numbers
 *  from 1 to 20?
*/

#include <stdio.h>

typedef int bool;
#define true 1
#define false 0


int main() {
    int num = 2520;
    bool notDivisible = true;

    while(notDivisible) {
        for(int i = 2; i <= 20; i++) {
            if(num % i == 0) {
                if(i == 20) {
                    notDivisible = false;
                    break; }
                continue; }
            else {
                num++;
                break; }}}

    printf("Num = %d\n", num);
    return 0; }
