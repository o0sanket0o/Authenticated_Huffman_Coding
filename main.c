#include <stdio.h>
#include <string.h>
#include "tree.c"
#include <sys/time.h>
#include <stdlib.h>

int main() {
	char a[100];
	struct timeval before;
	gettimeofday(&before, NULL);
	long long t1 = before.tv_sec * 1000 + before.tv_usec / 1000;
	scanf("%[^\n]s",a);
	userPair arr[128];
	Tree* store[128];
	for(int i = 0; i < 128; i++){
		arr[i].charCount = 0;
		arr[i].value = i;
	}
	for(int i = 0; a[i] != '\0'; ++i){
		arr[a[i]].charCount++;
		arr[a[i]].value = a[i];
	} 
	struct timeval after;
	int ind = 0, n = 0;
	for(int i = 0; i < 128; i++){
		if(arr[i].charCount != 0){
			Tree* temp = create(arr[i].charCount, arr[i].value, NULL, NULL);
			store[ind++] = temp;
			n++;
		}
	}
	Tree* root = combine(store, n);
	Tree* temp = (Tree*) malloc (sizeof(Tree));
	gettimeofday(&after, NULL);
	long long t2 = after.tv_sec * 1000 + after.tv_usec / 1000;
	printf("Time taken to encode the string is : %llums.\n", t2 - t1);
	temp = root;
	temp = root;
	char* ans = (char *) malloc(100 * sizeof(char));
	ind = 0;
	preorder(temp, ans, ind);
	return 0;
}
