#include <stdio.h>
#include <string.h>
#include "tree.c"

int main() {
	char a[100];
	scanf("%[^\n]s",a);
	printf("%s\n",a);
	userPair arr[128];
	Tree* store[128];
	for(int i = 0; i < 128; i++){
		arr[i].charCount = 0;
		arr[i].value = i;
	}
	for(int i = 0; a[i] != '\0'; ++i){
		// printf("%d\n", i);
		arr[a[i]].charCount++;
		arr[a[i]].value = a[i];
	} 
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
	temp = root;
	printf("\nPreorder:\n");
	preorder(temp);
	temp = root;
	printf("\nInorder:\n");
	inorder(temp);
	return 0;
}
