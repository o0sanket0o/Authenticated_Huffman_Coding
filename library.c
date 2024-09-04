#include <stdio.h>
#include <CommonCrypto/CommonCrypto.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

// Global string containing possible characters for random password generation
char *chars = "01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%{}[]<>./?^&*()";

// Function to generate a random password of length `n` using characters from `chars`
char* createPassWord(int n, int sz) {
    char* generate = (char *)malloc(n * sizeof(char));  // Allocates memory for password
    srand(time(NULL));  // Seed the random number generator with the current time
    for (int i = 0; i < n; i++) 
        generate[i] = chars[rand() % sz];  // Select random characters from "chars" string
    return generate;
}

// Function to log the time of a successful login or password change
void loginHistory(bool change) {
    time_t t = time(NULL);  // Get the current time
    struct tm *tm = localtime(&t);  // Convert to local time
    char s[164];  // Buffer to store formatted time string
    size_t ret = strftime(s, sizeof(s), "%c", tm);  // Format time as a string

    if (ret == 0) {
        perror("strftime failed");  // Error handling for time formatting
        return;
    }

    // Print the length of the time string and the string itself (for debugging)
    printf("%lu\n", strlen(s));
    printf("%s\n", s);

    // Open the history file in append mode
    int fd = open("history.txt", O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("open");  // Error handling for file opening
        return;
    }

    // Prepare the log entry string based on whether it's a password change or a login
    char info[200];
    if (change) 
        strcpy(info, "Password updated on: ");
    else 
        strcpy(info, "Successful login on: ");
    strcat(info, s);
    strcat(info, "\n");

    // Write the log entry to the file
    ssize_t sz = write(fd, info, strlen(info));
    if (sz < 0) {
        perror("write");  // Error handling for file writing
    }

    close(fd);  // Close the file descriptor
}

// Function to hash a password using SHA-256
void hashPassword(const char *password, unsigned char hash[CC_SHA256_DIGEST_LENGTH]) {
    CC_SHA256_CTX sha256;  // SHA-256 context
    CC_SHA256_Init(&sha256);  // Initialize SHA-256 context
    CC_SHA256_Update(&sha256, password, strlen(password));  // Update hash with password data
    CC_SHA256_Final(hash, &sha256);  // Finalize hash
}

// Function to print a SHA-256 hash as a hexadecimal string
void printHash(const unsigned char hash[CC_SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < CC_SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);  // Print each byte as a two-digit hexadecimal number
    }
    printf("\n");
}

// Function to compare two SHA-256 hashes
int compareHashes(const unsigned char hash1[CC_SHA256_DIGEST_LENGTH], const unsigned char hash2[CC_SHA256_DIGEST_LENGTH]) {
    return memcmp(hash1, hash2, CC_SHA256_DIGEST_LENGTH) == 0;  // Return 1 if hashes are equal, 0 otherwise
}

// Function to convert a hexadecimal string to a byte array (SHA-256 hash)
void hexStringToBytes(const char *hexString, unsigned char *hash) {
    for (int i = 0; i < CC_SHA256_DIGEST_LENGTH; i++) {
        sscanf(hexString + 2 * i, "%2hhx", &hash[i]);  // Convert each pair of hex digits to a byte
    }
}

// Function to read a SHA-256 hash from a file
bool readHashFromFile(const char *filename, unsigned char hash[CC_SHA256_DIGEST_LENGTH]) {
    FILE *file = fopen(filename, "r");  // Open the file for reading
    if (file == NULL) {
        perror("Failed to open file");  // Error handling for file opening
        return false;
    }

    // Read the hexadecimal hash string from the file
    char hexHash[2 * CC_SHA256_DIGEST_LENGTH + 1];
    if (fgets(hexHash, sizeof(hexHash), file) != NULL) {
        hexHash[strcspn(hexHash, "\n")] = '\0';  // Remove newline character
        hexStringToBytes(hexHash, hash);  // Convert hex string to byte array
        fclose(file);  // Close the file
        return true;
    }

    fclose(file);  // Close the file if reading failed
    return false;
}

// Function to write a SHA-256 hash to a file
void writeHashToFile(const char *filename, const unsigned char hash[CC_SHA256_DIGEST_LENGTH]) {
    FILE *file = fopen(filename, "w");  // Open the file for writing
    if (file == NULL) {
        perror("Failed to open file for writing");  // Error handling for file opening
        return;
    }

    // Write the hash as a hexadecimal string to the file
    for (int i = 0; i < CC_SHA256_DIGEST_LENGTH; i++) {
        fprintf(file, "%02x", hash[i]);  // Write each byte as a two-digit hexadecimal number
    }

    fclose(file);  // Close the file
}

// Function to check the entered password against the stored hash
bool checkPass(char *userPassword) {
    unsigned char hash[CC_SHA256_DIGEST_LENGTH];
    hashPassword(userPassword, hash);  // Hash the entered password

    unsigned char hashToVerify[CC_SHA256_DIGEST_LENGTH];
    if (!readHashFromFile("pass.txt", hashToVerify)) {  // Read the stored hash from the file
        printf("Failed to read hash from file.\n");
        return false;
    }

    if (compareHashes(hash, hashToVerify)) {  // Compare the hashes
        printf("Password verification successful.\n");
        return true;
    } else {
        printf("Wrong password.\n");
        printf("Enter 1 to change the password.\nEnter 2 to exit the program.\n");
        int num;
        scanf("%d", &num);
        getchar();  // Consumes the newline character
        if(num == 1){
            int choice;
            char *newPassword = NULL;
            printf("Enter 1 to generate a random password.\nEnter 2 to create your own password.\n");
            scanf("%d", &choice);
            getchar();  // Consumes the newline character
            if (choice == 1) {
                int sz = strlen(chars);  // Get the length of the "chars" string
                newPassword = createPassWord(10, sz);  // Generates a random password of length 10
                if (newPassword == NULL) {
                    printf("Error generating password.\n");
                    return false;
                }
                printf("Your new password is: %s\n", newPassword);
            } else if (choice == 2) {
                newPassword = (char *)malloc(200 * sizeof(char));  // Allocates memory for new password
                if (newPassword == NULL) {
                    printf("Memory allocation failed.\n");
                    return false;
                }
                printf("Enter the new password: ");
                fgets(newPassword, 200, stdin);  // Read the new password from the user

                size_t len = strlen(newPassword);
                if (len > 0 && newPassword[len - 1] == '\n') {
                    newPassword[len - 1] = '\0';  // Removed newline character from the end of the password
                }
            }
            unsigned char newHash[CC_SHA256_DIGEST_LENGTH];
            hashPassword(newPassword, newHash);  // Hash the new password
            writeHashToFile("pass.txt", newHash);  // Write the new hash to the file
            loginHistory(true);  // Log the password change
            printf("Password changed successfully.\n");

            if (newPassword != NULL) {
                free(newPassword);  // Free allocated memory
            }
        } else printf("Program ended.\n");
    }
    return false;
}

