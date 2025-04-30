#include <stdio.h>
#include <stdlib.h>

// a : 3X**7 + 7X**5 - 2X**3 + 9X**2 + 10;
// b : 8X**6 + 3X**4 + 4X**2 + 7X**1 + 9;

struct Poly {
    int exp;    // 지수
    int coef;   // 계수
    struct Poly * next;
};

void InitList(struct Poly ** head, struct Poly ** tail, int * exp, int * coef, int size);
void PrintList(struct Poly * ptr);
void FreeList(struct Poly * head);
void AddList();



const int SIZE = 5;
struct Poly* aHead=NULL, *aTail=NULL, *bHead=NULL, *bTail=NULL;
struct Poly* cHead=NULL, *cTail=NULL;


int main() {
    int aExp[SIZE] = {7, 5, 3, 2, 0};
    int aCoef[SIZE] = {3, 7, -2, 9, 10};
    int bExp[SIZE] = {6, 4, 2, 1, 0};
    int bCoef[SIZE] = {8, 3, 4, 7, 9};

    InitList(&aHead, &aTail, aExp, aCoef, SIZE);
    InitList(&bHead, &bTail, bExp, bCoef, SIZE);

    PrintList(aHead);
    PrintList(bHead);

    AddList();
    PrintList(cHead);

    FreeList(aHead);
    FreeList(bHead);
    FreeList(cHead);
    return 0;
}

void InitList(struct Poly ** head, struct Poly ** tail, int * exp, int * coef, int size) {

    struct Poly* newNode;

    for (int i=0; i<size; i++) {
        newNode = (struct Poly*)malloc(sizeof(struct Poly));

        newNode->exp = exp[i];
        newNode->coef = coef[i];
        newNode->next = NULL;

        if (*head == NULL) *head = newNode;
        else (*tail)->next = newNode;
        *tail = newNode;
    }
}

void PrintList(struct Poly * ptr) {
    int cnt = 0;
    while (ptr != NULL) {
        if (ptr->coef > 0) {
            if (cnt == 0) printf("%dX**%d", ptr->coef, ptr->exp);
            else if (ptr->exp == 0) printf("+%d", ptr->coef);
            else if (ptr->coef == 1) printf("+X**%d", ptr->exp);
            else printf("+%dX**%d", ptr->coef, ptr->exp);
        }
        else if (ptr->coef < 0) {
            if (cnt == 0) printf("%dX**%d", ptr->coef, ptr->exp);
            else if (ptr->exp == 0) printf("%d", ptr->coef);
            else if (ptr->coef == -1) printf("-X**%d", ptr->exp);
            else printf("%dX**%d", ptr->coef, ptr->exp);
        }
        ptr = ptr->next;
        cnt++;
    }
    printf("\n");
}
void AddList() {
    struct Poly * aCur, *bCur;
    int i=0;
    int cExp[SIZE*2];
    int cCoef[SIZE*2];
    aCur = aHead;
    bCur = bHead;

    while (aCur != NULL && bCur != NULL) {
        if (aCur->exp == bCur->exp) {
            cCoef[i] = aCur->coef + bCur->coef;
            cExp[i++] = aCur->exp;
            aCur = aCur->next;
            bCur = bCur->next;
        }
        else if (aCur->exp > bCur->exp) {
            cCoef[i] = aCur->coef;
            cExp[i++] = aCur->exp;
            aCur = aCur->next;
        }
        else if (bCur->exp > aCur->exp) {
            cCoef[i] = bCur->coef;
            cExp[i++] = bCur->exp;
            bCur = bCur->next;
        }
    }

    while (aCur != NULL) {
        cCoef[i] = aCur->coef;
        cExp[i++] = aCur->exp;
        aCur = aCur->next;
    }

    while (bCur != NULL) {
        cCoef[i] = bCur->coef;
        cExp[i++] = bCur->exp;
        bCur = bCur->next;
    }
    InitList(&cHead, &cTail, cExp, cCoef, i);
}

void FreeList(struct Poly* head) {
    struct Poly* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
