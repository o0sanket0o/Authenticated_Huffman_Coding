#include <stdio.h>

int main() {
    char str[100];
    printf("Enter the string you want to encode:");
    scanf("%[^\n]s",str);
    printf("You entered: %s\n",str);
    
    return 0;
}
