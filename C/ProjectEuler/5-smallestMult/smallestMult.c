#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

int main() {
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

    return 0; }
