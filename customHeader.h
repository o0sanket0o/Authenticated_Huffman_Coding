#include <CommonCrypto/CommonCrypto.h>
#include <stdbool.h>

// Function Declarations
void hashPassword(const char *password, unsigned char hash[CC_SHA256_DIGEST_LENGTH]);
void printHash(const unsigned char hash[CC_SHA256_DIGEST_LENGTH]);
int compareHashes(const unsigned char hash1[CC_SHA256_DIGEST_LENGTH], const unsigned char hash2[CC_SHA256_DIGEST_LENGTH]);
void hexStringToBytes(const char *hexString, unsigned char *hash);
bool readHashFromFile(const char *filename, unsigned char hash[CC_SHA256_DIGEST_LENGTH]);
void writeHashToFile(const char *filename, const unsigned char hash[CC_SHA256_DIGEST_LENGTH]);
bool checkPass(char *userPassword);
void loginHistory(bool change);
char* createPassWord(int n, int sz);

