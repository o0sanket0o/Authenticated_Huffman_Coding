#include <stdio.h>
#include <stdlib.h>

//Define a pair which store the characters and counts 
typedef struct{
	int charCount;
	char value;
}userPair;

// Define a struct to represent a tree node
typedef struct TreeNode{
	int count;
	char value;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;

//Function to swap the elements of array
void swap(Tree* arr[], int i, int j){
	Tree* temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

//Function to heapify the array of Trees
void heapify(Tree* arr[], int i, int n){
	int left = 2 * i + 1, right = 2 * i + 2, temp = i;
	if(left < n && arr[left] -> count < arr[temp] -> count) temp = left;
	if(right < n && arr[right] -> count < arr[temp] -> count) temp = right;
	if(temp != i){
		swap(arr, i, temp);
		heapify(arr, temp, n);
	}
}

//Define a function to heapify whenever required
void makeHeap(Tree* arr[], int n){
	int leaves = (n + 1) / 2;
	for(int i = n - leaves - 1; i >= 0; i--){
		heapify(arr, i, n);
	}
}

//Define a function to create node of a tree
Tree* create(int data, char c, Tree* leftNode, Tree* rightNode){
	Tree* root = (Tree*) malloc (sizeof(Tree));
	root -> count = data;
	root -> value = c;
	root -> left = leftNode;
	root -> right = rightNode;
	return root;
}

//The main function which will keep updating the tree using the heap
Tree* combine(Tree* store[], int n){
	if(n == 1) return store[0];
	Tree* first = store[0];
	for(int i = 0; i < n - 1; i++){
		store[i] = store[i + 1];
	}
	--n;
	makeHeap(store, n);
	Tree* second = store[0];
	for(int i = 0; i < n - 1; i++){
		store[i] = store[i + 1];
	}
	--n;
	Tree* l = (Tree *) malloc( sizeof( Tree ));
	Tree* r = (Tree *) malloc( sizeof( Tree ));
	if(first -> count < second -> count){
		l = first;
		r = second;
	}else{
		l = second;
		r = first;
	}
	Tree* parent = create(first -> count + second -> count, '~', l, r);
	++n;
	store[n - 1] = parent;
	makeHeap(store, n);
	return combine(store, n);
}

//Define a function to see the mapping of each character
void preorder(Tree* root, char* ans, int i){
	if(!root -> left && !root -> right){
		printf("%c --> ", root -> value);
		for(int a = 0; a <= i; a++) printf("%c", ans[a]);
		printf("\n");
		return;
	}
	ans[i] = '0';
	preorder(root -> left, ans, i + 1);
	ans[i] = '1';
	preorder(root -> right, ans, i + 1);
}




