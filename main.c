#include "customHeader.h"  
#include "huffman.c"      
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    int n = 2;  // Number of strings to be input (password and string to encode)
    char **strings = (char **)malloc(n * sizeof(char *));  // Allocate memory for storing `n` strings
    bool pass = true;  // Flag to determine whether to prompt for password or the string to encode
    for (int i = 0; i < n; i++) {
        strings[i] = (char *)malloc(300 * sizeof(char));  // Allocate memory for each string
        if (pass) {
            // Asks the user to enter password
            printf("Enter password: ");
            fgets(strings[i], 200, stdin);  // Read the password from stdin 
            pass = !pass;  // Toggle the `pass` flag
        } else {
            pass = !pass;  // Toggle the `pass` flag
            // Prompt user to enter the string they want to encode
            printf("Enter the string you want to encode: ");
            fgets(strings[i], 300, stdin);  // Read the string to encode 
        }

        // Remove the newline character from the end of the string, if present
        size_t len = strlen(strings[i]);
        if (len > 0 && strings[i][len - 1] == '\n') {
            strings[i][len - 1] = '\0';
        }
    }

    // Check if the entered password is correct
    if (checkPass(strings[0])) {
        loginHistory(false);  // Write the login details in history.txt via library.c
        implementHuffman(strings[1]);  // Performs Huffman encoding on the input string
    }

    // Free allocated memory for the strings
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);  // Free the memory allocated for the array of strings

    return 0;
}

