#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define key 600851475143
#define primeMax 10000

int main() {
    int primes[primeMax] = {5};
    int largestPrime = 0;
    int tempPrime = 0;
    double n = primeMax;

    for(int i = 2; i < n; i++) {
        primes[i] = true; }

    for(int i = 2; i < sqrt(n); i++) {
        if(primes[i] == true) {
            for(int j = i*i; j < n; j+=i)
                primes[j] = false; }}

    for(int i = 2; i < n; i++) {
        if(primes[i] == true && key % i == 0) {
            printf("%d\n", i);
            tempPrime = i;
            if(tempPrime > largestPrime) largestPrime = tempPrime; }}

    printf("Largest prime: %d\n", largestPrime);
    return 0;}
