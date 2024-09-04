#include <stdio.h>
#include <string.h>
#include "tree.c"  // Include the Huffman tree implementation
#include <sys/time.h>
#include <stdlib.h>

// Function to implement Huffman encoding on the input string `a`
void implementHuffman(char *a) {
    struct timeval before;  // Struct to hold the start time of the encoding process
    gettimeofday(&before, NULL);  // Get the current time before starting the process
    long long t1 = before.tv_sec * 1000 + before.tv_usec / 1000;  // Convert time to milliseconds

    userPair arr[128];  // Array to store frequency of each character (ASCII values from 0 to 127)
    Tree* store[128];   // Array to store nodes for Huffman tree

    // Initialize the character frequency array
    for (int i = 0; i < 128; i++) {
        arr[i].charCount = 0;
        arr[i].value = i;
    }

    // Count the frequency of each character in the input string
    for (int i = 0; a[i] != '\0'; ++i) {
        arr[a[i]].charCount++;
        arr[a[i]].value = a[i];
    }

    struct timeval after;  // Struct to hold the end time of the frequency counting process
    int ind = 0, n = 0;

    // Create nodes for each character with non-zero frequency
    for (int i = 0; i < 128; i++) {
        if (arr[i].charCount != 0) {
            Tree* temp = create(arr[i].charCount, arr[i].value, NULL, NULL);  // Create a new tree node
            store[ind++] = temp;  // Store the node in the array
            n++;
        }
    }

    // Combine nodes to create the Huffman tree
    Tree* root = combine(store, n);
    Tree* temp = (Tree*) malloc (sizeof(Tree));

    gettimeofday(&after, NULL);  // Get the current time after creating the tree
    long long t2 = after.tv_sec * 1000 + after.tv_usec / 1000;  // Convert time to milliseconds

    temp = root;  // Set temp to root (root of Huffman tree)
    char* ans = (char *) malloc(100 * sizeof(char));  // Allocate memory for storing encoded string
    ind = 0;

    // Traverse the Huffman tree in preorder and generate the encoded string
    preorder(temp, ans, ind);

    // Print the time taken to encode the string
    printf("Time taken to encode the string is : %llums.\n", t2 - t1);

    // Free allocated memory (if needed in the future implementation)
    free(ans);
    free(temp);
}

