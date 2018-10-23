/*
 *  By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13,
 *  we can see that the 6th prime is 13.
 *
 *  What is the 10 001st prime number?
 */

#include <stdio.h>
#include <error.h>
#include <stdlib.h>

int main() {
    FILE * file = fopen("/home/jtlikesponies/Documents/Misc/my-resume.pdf", "r");
    if(file == NULL) perror("Failed to open file");
    else {
        printf("File opened successfully\n");
        fclose(file); }

    return 0; }
