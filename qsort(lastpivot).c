#include <stdio.h>
#define size 15

int A[size];

int swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int part(int A[size], int p, int r) {
    int x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++) {
        if (A[j] <= x) {
            i += 1;
            swap (&A[i], &A[j]);
        }
    }
    swap(&A[i], &A[p]);            //swap the pivot with the element in A[i]
    return i;
}

int qsort(int A[size], int p, int r) {
    int q;
    if (p < r) {
        q = part(A, p, r);
        qsort(A, p, q-1);
        qsort(A, q+1, r);
    }
}

int main() {
    int n;
    printf("Enter the size of the Array (within %d): ", size);
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        printf("Enter the %dth element: ", i+1);
        scanf("%d", &A[i]);
    }

    qsort(A, 0, n-1);

    printf("The Sorted array:\n");
    for(int i=0; i<n; i++) {
        printf("%d ", A[i]);
    }
}