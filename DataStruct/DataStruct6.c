#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int * arr);
int median(int * arr);
void swap(int * a, int * b);
void quickSort(int * arr, int start, int end);
int partition(int * arr, int start, int end);
void bubbleSort(int * arr, int start, int end);
void printArr(int * arr);

int size = 30;

int main() {
    int m;
    int arr[size];
    init(arr);
    printf("초기 상태: \n");
    printArr(arr);
    m = median(arr);
    if (m!=0) swap(&arr[0], &arr[m]);
    printf("피벗 변경: \n");
    printArr(arr);
    quickSort(arr, 0, size-1);
    printArr(arr);
    return 0;
}

void init(int * arr) {
    srand(time(NULL));
    for (int i=0; i<size; i++) {
        arr[i] = (rand() % size)+1;
    }
}

int median(int * arr) {
    int temp[3] = {0, size/2, size-1};
    int copy[3] = {arr[0], arr[size/2], arr[size-1]};

    bubbleSort(copy, 0, 2);

    for (int i=0; i<3; i++)
        if (arr[temp[i]] == copy[1]) return temp[i];

    return -1;
}

void bubbleSort(int * arr, int start, int end) {
    for (int i=end; i>start; i--) {
        for (int j=start; j<i; j++) {
            if (arr[j] > arr[j+1]) swap(&arr[j], &arr[j+1]);
        }
    }
}

void quickSort(int * arr, int start, int end) {
    if (start < end) {
        if (end - start + 1 <= 6) {
            bubbleSort(arr, start, end);
            printf("BubbleSort! (구간 %d~%d):\n", start, end);
            printArr(arr);
            return;
        }

        int pivot = partition(arr, start, end);
        quickSort(arr, start, pivot-1);
        quickSort(arr, pivot+1, end);
    }
}

int partition(int * arr, int start, int end) {
    int low, high;
    int pivot = arr[start];

    printf("pivot: %d \n", pivot);

    low = start + 1;
    high = end;

    while (low <= high) {
        while (low <= end &&arr[low] < pivot) low++;
        while (high > start && arr[high] > pivot) high--;

        if (low <= high) {
            swap(&arr[low], &arr[high]);
            low++;
            high--;
        }
    }
    swap(&arr[start],&arr[high]);
    printArr(arr);
    return high;
}

void swap(int * a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArr(int * arr) {
    printf("[ ");
    for (int i=0; i<size; i++) {
        printf("%3d ", arr[i]);
    }
    printf("] \n\n");
}