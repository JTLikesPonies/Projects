#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


/* Prepends t into s. Assumes s has enough space allocated
** for the combined string.
*/
void prepend(char* s)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}


int main()
{
    char* s = malloc(100);
    strcpy(s, "file");
    prepend(s, "dir/");

    printf("%s\n", s);
    return 0;
}
