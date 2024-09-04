#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *chars = "01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%{}[]<>./?^&*()";
char* createPassWord(int n, int sz){
    char* generate = (char *) malloc (n * sizeof(char));
    srand(time(NULL));
    for(int i = 0; i < n; i++) generate[i] = chars[rand() % sz];
    return generate;
}
