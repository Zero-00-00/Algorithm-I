#include <stdio.h>
#define size 2  // Matrix size (must be a power of 2)

int A[size][size], B[size][size], C[size][size];

// Function to add two matrices
void add(int A[size][size], int B[size][size], int C[size][size], int split) {
    for (int i = 0; i < split; i++) {
        for (int j = 0; j < split; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtract(int A[size][size], int B[size][size], int C[size][size], int split) {
    for (int i = 0; i < split; i++) {
        for (int j = 0; j < split; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's Algorithm
void strassen(int A[size][size], int B[size][size], int C[size][size], int split) {
    if (split == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = split / 2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int P1[newSize][newSize], P2[newSize][newSize], P3[newSize][newSize], P4[newSize][newSize];
    int P5[newSize][newSize], P6[newSize][newSize], P7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];

    // Dividing matrices into sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // P1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, newSize);
    add(B11, B22, temp2, newSize);
    strassen(temp1, temp2, P1, newSize);

    // P2 = (A21 + A22) * B11
    add(A21, A22, temp1, newSize);
    strassen(temp1, B11, P2, newSize);

    // P3 = A11 * (B12 - B22)
    subtract(B12, B22, temp1, newSize);
    strassen(A11, temp1, P3, newSize);

    // P4 = A22 * (B21 - B11)
    subtract(B21, B11, temp1, newSize);
    strassen(A22, temp1, P4, newSize);

    // P5 = (A11 + A12) * B22
    add(A11, A12, temp1, newSize);
    strassen(temp1, B22, P5, newSize);

    // P6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, temp1, newSize);
    add(B11, B12, temp2, newSize);
    strassen(temp1, temp2, P6, newSize);

    // P7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, newSize);
    add(B21, B22, temp2, newSize);
    strassen(temp1, temp2, P7, newSize);

    // Combining results into matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];  // C11
            C[i][j + newSize] = P3[i][j] + P5[i][j];              // C12
            C[i + newSize][j] = P2[i][j] + P4[i][j];              // C21
            C[i + newSize][j + newSize] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];  // C22
        }
    }
}

// Function to display the matrix
void display(int matrix[size][size], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = size;

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Perform Strassen multiplication
    strassen(A, B, C, n);

    printf("\nResultant Matrix C (A x B):\n");
    display(C, n);

    return 0;
}
