#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int charCount;
    char value;
}userPair;

typedef struct TreeNode{
    int count;
    char value;
    struct TreeNode* left;
    struct TreeNode* right;
}Tree;
void swap(Tree* arr[], int i, int j){
    Tree* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapify(Tree* arr[], int i, int n){
    int left = 2 * i + 1, right = 2 * i + 2, temp = i;
    if(left < n && arr[left] -> count < arr[temp] -> count) temp = left;
    if(right < n && arr[right] -> count < arr[temp] -> count) temp = right;
    if(temp != i){
        swap(arr, i, temp);
        heapify(arr, temp, n);
    }
}
void makeHeap(Tree* arr[], int n){
    int leaves = (n + 1) / 2;
    for(int i = n - leaves - 1; i >= 0; i--){
        heapify(arr, i, n);
    }
}


Tree* create(int data, char c, Tree* leftNode, Tree* rightNode){
    Tree* root = (Tree*) malloc (sizeof(Tree));
    root -> count = data;
    root -> value = c;
    root -> left = leftNode;
    root -> right = rightNode;
    return root;
}

Tree* combine(Tree* store[], int n){
//    print(store, n);
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
    // printf("%c --> %d\n", parent -> value, parent -> count);
    // printf("%c --> %d\n", l -> value, l -> count);
    // printf("%c --> %d\n", r -> value, r -> count);
    store[n - 1] = parent;
    makeHeap(store, n);
    return combine(store, n);
}

void inorder(Tree *root){
    if(!root) return;
    inorder(root->left);
    printf("%c --> %d\n", root -> value, root -> count);
    inorder(root -> right);
}
void preorder(Tree *root){
    if(!root) return;
    printf("%c --> %d\n", root -> value, root -> count);
    preorder(root->left);
    preorder(root -> right);
}




