#include <stdio.h>
#include "election.h"
#include <stdlib.h>
char* toString(int num);
int toInt(char* str);

int main() {
    int x = 456;
    char* str = toString(x);
    printf("%s",str);
    free(str);
    return 0;
}