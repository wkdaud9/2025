#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct BST{
    int data;
    struct BST * Right;
    struct BST * Left;
}BST;

int max(int a, int b);
void input();
void addNode(int n);
BST* search(int n);
void insertNode(BST* cur);
int getHeight(BST* cur);
void saveArrNode(BST * cur, int idx);
void printBST(int size);
void printArr(int size);
void printSearch(int n);

BST * head = NULL;
int * arr;

// input Num : 6 3 9 2 5 8 11 1 4 7 10 12

int main() {
    double max_size;
    int max_temp;
    int n = 12;

    for (int i=0; i<n; i++) input();

    max_temp = getHeight(head);
    max_size = pow(2, max_temp);
    arr = (int*)malloc(sizeof(int)*(int)max_size-1);
    saveArrNode(head, 1);

    printBST((int)max_size);
    printf("탐색 키: 1, [");
    printSearch(1);
    printf("탐색 키: 12, [");
    printSearch(12);

    printArr((int)max_size);

    return 0;
}

void input() {
    int n;
    scanf("%d", &n);
    addNode(n);
}

void addNode(int n) {
    BST * cur = (BST*)malloc(sizeof(BST));
    cur ->data = n;
    cur -> Right = cur->Left = NULL;
    insertNode(cur);
}

void insertNode(BST*cur) {
    BST * temp;
    if (head == NULL) head = cur;
    else {
        temp = search(cur->data);
        if (temp-> data > cur->data) temp->Left = cur;
        else if (cur->data > temp->data) temp->Right = cur;
    }
}

BST* search(int n) {
    BST * temp;
    temp = head;
    while (1) {
        if (temp->data > n) {
            if (temp->Left == NULL) return temp;
            temp = temp->Left;
        }
        else if (temp->data < n) {
            if (temp->Right == NULL) return temp;
            temp = temp->Right;
        }
    }
}

int getHeight(BST* cur) {
    int height = 0;
    if (cur != NULL) height = 1 + max(getHeight(cur->Left), getHeight(cur->Right));
    return height;
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

void saveArrNode(BST * cur, int idx) {
    if (cur == NULL) return;
    arr[idx] = cur->data;
    saveArrNode(cur->Left, 2*idx);
    saveArrNode(cur->Right, (2*idx)+1);
}

void printBST(int size) {
    int idx[4] = {1,3,6,7};

    printf("\n");
    printf("             %d\n", arr[idx[0]]);
    printf("          /      \\\n");
    printf("        %d         %d\n", arr[idx[0]*2], arr[idx[0]*2+1]);
    idx[0]++;
    printf("      /   \\     /   \\\n");
    printf("     %d     %d   %d     %d\n",arr[idx[0]*2], arr[idx[0]*2+1], arr[idx[1]*2], arr[idx[1]*2+1]);
    printf("    /     /   /      / \\\n");
    idx[0]*=2;
    idx[1]+=2;
    printf("   %d     %d   %d      %d  %d\n", arr[idx[0]*2], arr[idx[1]*2], arr[idx[2]*2], arr[idx[3]*2], arr[idx[3]*2+1]);
    printf("\n");
}

void printSearch(int n) {
    BST * temp = head;
    while (1) {
        if (temp->data == n) {
            printf("%d] \n", temp->data);
            return;
        }
        else if (temp -> data < n) {
            printf("%d, ", temp->data);
            temp = temp -> Right;
        }
        else if (temp->data > n) {
            printf("%d, ", temp->data);
            temp = temp->Left;
        }
    }
}

void printArr(int size) {
    printf("\n");
    printf("Index: ");
    for (int i=0; i<size; i++)
        printf("|%2d| ", i);
    printf("\n");
    printf("Value: ");
    for (int i=0; i<size; i++) {
        if (arr[i] != 0) {
            printf("|%2d| ", arr[i]);
        }
        else if (arr[i] == 0) {
            printf("|  | ");
        }
    }
    printf("\n");
}