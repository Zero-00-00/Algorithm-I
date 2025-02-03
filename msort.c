#include <stdio.h>
#define size 15

int A[size];

int merge(int A[size], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], R[n2];
    for (int i=0; i<n1; i++){
        L[i] = A[p + i];
    }
    for (int j=0; j<n2; j++){
        R[j] = A[q + j + 1];
    }
    L[n1]=999999, R[n2]=999999;

    int i = 0, j = 0;
    for(int k=p; k<=r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
    }
}

int msort(int A[size], int p, int r) {
    if (p < r) {
        int q = ((p+r)/2);
        msort(A, p, q);
        msort(A, q+1, r);
        merge(A, p, q, r);
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

    msort(A, 0, n-1);

    printf("The Sorted array:\n");
    for(int i=0; i<n; i++) {
        printf("%d ", A[i]);
    }
}