#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Function to allocate memory for a matrix
int** allocateMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to free dynamically allocated matrix
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void add(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtract(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's Algorithm
void strassen(int** A, int** B, int** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;

    // Allocate memory for submatrices
    int** A11 = allocateMatrix(newSize);
    int** A12 = allocateMatrix(newSize);
    int** A21 = allocateMatrix(newSize);
    int** A22 = allocateMatrix(newSize);
    int** B11 = allocateMatrix(newSize);
    int** B12 = allocateMatrix(newSize);
    int** B21 = allocateMatrix(newSize);
    int** B22 = allocateMatrix(newSize);
    int** C11 = allocateMatrix(newSize);
    int** C12 = allocateMatrix(newSize);
    int** C21 = allocateMatrix(newSize);
    int** C22 = allocateMatrix(newSize);
    int** P1 = allocateMatrix(newSize);
    int** P2 = allocateMatrix(newSize);
    int** P3 = allocateMatrix(newSize);
    int** P4 = allocateMatrix(newSize);
    int** P5 = allocateMatrix(newSize);
    int** P6 = allocateMatrix(newSize);
    int** P7 = allocateMatrix(newSize);
    int** temp1 = allocateMatrix(newSize);
    int** temp2 = allocateMatrix(newSize);

    // Divide A and B into submatrices
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

    // Compute the 7 Strassen products
    add(A11, A22, temp1, newSize);
    add(B11, B22, temp2, newSize);
    strassen(temp1, temp2, P1, newSize);

    add(A21, A22, temp1, newSize);
    strassen(temp1, B11, P2, newSize);

    subtract(B12, B22, temp1, newSize);
    strassen(A11, temp1, P3, newSize);

    subtract(B21, B11, temp1, newSize);
    strassen(A22, temp1, P4, newSize);

    add(A11, A12, temp1, newSize);
    strassen(temp1, B22, P5, newSize);

    subtract(A21, A11, temp1, newSize);
    add(B11, B12, temp2, newSize);
    strassen(temp1, temp2, P6, newSize);

    subtract(A12, A22, temp1, newSize);
    add(B21, B22, temp2, newSize);
    strassen(temp1, temp2, P7, newSize);

    // Compute final submatrices of C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C11[i][j] = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];
            C12[i][j] = P3[i][j] + P5[i][j];
            C21[i][j] = P2[i][j] + P4[i][j];
            C22[i][j] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];
        }
    }

    // Merge C11, C12, C21, C22 into C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free allocated memory
    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(P1, newSize); freeMatrix(P2, newSize);
    freeMatrix(P3, newSize); freeMatrix(P4, newSize);
    freeMatrix(P5, newSize); freeMatrix(P6, newSize);
    freeMatrix(P7, newSize); freeMatrix(temp1, newSize);
    freeMatrix(temp2, newSize);
}

// Function to print a matrix
void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int size;
    printf("Enter the size: ");
    scanf("%d", &size);
    
    int** A = allocateMatrix(size);
    int** B = allocateMatrix(size);
    int** C = allocateMatrix(size);

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            scanf("%d", &B[i][j]);

    strassen(A, B, C, size);

    printf("Resultant Matrix C:\n");
    printMatrix(C, size);

    freeMatrix(A, size); freeMatrix(B, size); freeMatrix(C, size);
    return 0;
}
