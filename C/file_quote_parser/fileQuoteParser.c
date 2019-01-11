#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

char * append(char *line) {
    char * newLine = malloc(strlen(line) + 2);
    int len = strlen(newLine);

    if(line[0] == '\n') return line;
    else {
        for(int i = 0; i < strlen(line); i++) {
            newLine[i] = line[i]; }
        newLine[strlen(line)-1] = '\"';
        newLine[strlen(line)] = '\n'; }

    return newLine; }



char * prepend(char *line) {
    char * newLine = malloc(strlen(line) + 1);

    if(line[0] == '\n') return line;
    else {
        newLine[0] = '\"';
        for(int i = 0; i < strlen(line); i++) {
            newLine[i+1] = line[i]; }}

    return newLine; }



int main(int argc, char* argv[]) {
    FILE *file = fopen("text.txt", "r");
    char *line, *prepLine, *appLine;

    if(file) {
        fseek(file, 0L, SEEK_END);
        int length = ftell(file);
        fseek(file, 0L, SEEK_SET);
        char buf[4096];

        while((line = fgets(buf, sizeof(buf), file)) != NULL) {
            printf("%ld\n", strlen(line));
            prepLine = prepend(line);
            appLine = append(prepLine);
            puts(appLine); }}
    else perror("Failure opening file: ");

    fclose(file);
    return 0; }
